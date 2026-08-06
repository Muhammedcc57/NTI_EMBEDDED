/*
 ******************************************************************************
 * File    : main.c
 * Project : Battery Charger Simulator
 * MCU     : ATmega32  |  F_CPU : 8MHz
 ******************************************************************************
 */

#define F_CPU 8000000UL
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_int.h"
#include "ADC_interface.h"
#include "LCD_int.h"
#include "KPD_int.h"
#include "EXTI_int.h"
#include "GIE_int.h"
#include "TIM0_int.h"

/*============================================================================
 * Pin Definitions
 *============================================================================*/
#define CHARGER_PORT       PORTB
#define CHARGER_PIN        PIN0    /* Relay: HIGH=charging ON   */

#define ALARM_PORT         PORTB
#define ALARM_PIN          PIN1    /* LED  : HIGH=alarm active  */

#define COMPLETE_PORT      PORTB
#define COMPLETE_PIN       PIN2    /* LED  : HIGH=charge done   */

/*============================================================================
 *  ADC Channel
 *============================================================================*/
#define BAT_VOLT_CH        ADC_CHANNEL0   /* PA0: battery voltage divider */
#define BAT_TEMP_CH        ADC_CHANNEL1   /* PA1: LM35 temperature sensor */

/*============================================================================
 *  Voltage Thresholds  (10-bit ADC, AVCC=5V, divider ratio=3 => 0-15V)
 *  Formula: ADC = (V_bat / 3) * (1024 / 5)
 *============================================================================*/
#define ABSORPTION_VOLT_ADC   (u16)((14.4f / 3.0f) * (1024.0f / 5.0f))  /* 14.4V */
#define OVERVOLTAGE_ADC       (u16)((14.5f / 3.0f) * (1024.0f / 5.0f))  /* 14.5V */

/*============================================================================
 *  Temperature Threshold  (LM35: 10mV/C, AVCC=5V)
 *  Formula: ADC = (Temp * 10) * 1024 / 5000
 *  45C => ADC = 92
 *============================================================================*/
#define OVERTEMP_ADC          (u16)(92u)   /* 45 degrees C */

/*============================================================================
 *  State Machine Timings  (seconds)
 *============================================================================*/
#define ABSORPTION_TIME_S     30u
#define FLOAT_TIME_S           5u

/*============================================================================
 *  Charge Modes  (selected by keypad)
 *============================================================================*/
#define MODE_NONE     0u
#define MODE_SLOW     1u   /* Key '1' */
#define MODE_FAST     2u   /* Key '2' */
#define MODE_TRICKLE  3u   /* Key '3' */

/*============================================================================
 *  Charger States
 *============================================================================*/
typedef enum
{
    STATE_IDLE        = 0,
    STATE_BULK        = 1,
    STATE_ABSORPTION  = 2,
    STATE_FLOAT       = 3,
    STATE_COMPLETE    = 4,
    STATE_ALARM       = 5,
    STATE_DISCONNECT  = 6
} ChargerState_t;

/*============================================================================
 *  Global Variables  (volatile because modified in ISR callbacks)
 *============================================================================*/
static volatile ChargerState_t G_State          = STATE_IDLE;
static volatile u8             G_ChargeMode     = MODE_NONE;
static volatile u8             G_SecondFlag     = 0u;  /* set every 1s by TIM0 */
static volatile u8             G_DisconnectFlag = 0u;  /* set by EXTI ISR      */
static volatile u16            G_AbsTimer       = 0u;
static volatile u16            G_FloatTimer     = 0u;

/* TIM0 CTC sub-counter
 * @ 8MHz, prescaler=1024, OCR0=124 => interrupt every ~16ms
 * 63 * 16ms ~ 1 second                                                       */
#define TICKS_PER_SEC   63u
static volatile u8 G_TickCnt = 0u;

/*============================================================================
 *  TIM0 CTC Callback — fires every ~16ms, counts to 1 second
 *============================================================================*/
static void TIM0_1sCallback(void)
{
    G_TickCnt++;
    if (G_TickCnt >= TICKS_PER_SEC)
    {
        G_TickCnt    = 0u;
        G_SecondFlag = 1u;   /* tell main loop: 1 second elapsed */
    }
}

/*============================================================================
 *  EXTI INT0 Callback — falling edge on PD2 => battery disconnected
 *============================================================================*/
static void EXTI0_DisconnectCallback(void)
{
    G_DisconnectFlag = 1u;
}

/*============================================================================
 *  Helper: convert ADC value to voltage string and send to LCD
 *  Format: "XX.XV"
 *============================================================================*/
static void LCD_PrintVoltage(u16 Copy_u16ADC)
{
    /* V_bat(mV) = ADC * 5000 * 3 / 1024  (divider ratio = 3) */
    u32 mV    = ((u32)Copy_u16ADC * 15000UL) / 1024UL;
    u8  volts = (u8)(mV / 1000u);
    u8  tenth = (u8)((mV % 1000u) / 100u);

    LCD_voidSendNumber((s32)volts);
    LCD_voidSendString(".");
    LCD_voidSendNumber((s32)tenth);
    LCD_voidSendString("V");
}

/*============================================================================
 *  Helper: convert ADC value to temperature and send to LCD
 *  Format: "XXC"
 *============================================================================*/
static void LCD_PrintTemp(u16 Copy_u16ADC)
{
    /* Temp(C) = ADC * 500 / 1024  (LM35: 10mV/C, AVCC=5V) */
    u16 temp = (u16)((u32)Copy_u16ADC * 500UL / 1024UL);

    LCD_voidSendNumber((s32)temp);
    LCD_voidSendString("C");
}

static void LCD_PrintState(void)
{
    LCD_voidGoToXY(0, 0);
    switch (G_State)
    {
        case STATE_IDLE:        LCD_voidSendString("State:IDLE      "); break;
        case STATE_BULK:        LCD_voidSendString("State:BULK      "); break;
        case STATE_ABSORPTION:  LCD_voidSendString("State:ABSORB    "); break;
        case STATE_FLOAT:       LCD_voidSendString("State:FLOAT     "); break;
        case STATE_COMPLETE:    LCD_voidSendString("State:COMPLETE  "); break;
        case STATE_ALARM:       LCD_voidSendString("**ALARM**       "); break;
        case STATE_DISCONNECT:  LCD_voidSendString("**DISCONNECT**  "); break;
        default:                                                          break;
    }
}

int main(void)
{
    u16 batADC  = 0u;
    u16 tempADC = 0u;
    u8  key     = KPD_NOT_PRESSED;

    /*------------------------------------------------------------------------
     *  Configure output pins (relay + LEDs)
     *------------------------------------------------------------------------*/
    DIO_voidSetPinDirection(CHARGER_PORT,  CHARGER_PIN,  OUTPUT);
    DIO_voidSetPinDirection(ALARM_PORT,    ALARM_PIN,    OUTPUT);
    DIO_voidSetPinDirection(COMPLETE_PORT, COMPLETE_PIN, OUTPUT);

    DIO_voidSetPinValue(CHARGER_PORT,  CHARGER_PIN,  LOW);
    DIO_voidSetPinValue(ALARM_PORT,    ALARM_PIN,    LOW);
    DIO_voidSetPinValue(COMPLETE_PORT, COMPLETE_PIN, LOW);

    /*------------------------------------------------------------------------
     *  Initialize all drivers
     *------------------------------------------------------------------------*/
    ADC_voidInit();
    LCD_voidInit();
    KPD_voidInit();

    /* EXTI INT0: falling edge on PD2 => emergency disconnect */
    EXTI_voidInit(EXTI_INT0, EXTI_FALLING_EDGE);
    EXTI_voidSetCallBack(EXTI_INT0, EXTI0_DisconnectCallback);
    EXTI_voidEnable(EXTI_INT0);

    /* Timer0 CTC: OCR0=124, prescaler=1024 => interrupt ~every 16ms */
    TIM0_voidInit();
    TIM0_voidSetCTCReg(124u);
    TIM0_voidCTCSetCallBack(TIM0_1sCallback);
    TIM0_voidEnableCTCInterrupt();

    /* Enable global interrupts */
    GIE_VoidEnable();

    /*------------------------------------------------------------------------
     *  Welcome screen
     *------------------------------------------------------------------------*/
    LCD_voidGoToXY(0, 0);
    LCD_voidSendString("Battery Charger ");
    LCD_voidGoToXY(1, 0);
    LCD_voidSendString(" Simulator v1.0 ");
    _delay_ms(2000);
    LCD_voidClear();

    /*------------------------------------------------------------------------
     *  Mode selection screen — block until user presses 1, 2, or 3
     *------------------------------------------------------------------------*/
    LCD_voidGoToXY(0, 0);
    LCD_voidSendString("Select Mode:    ");
    LCD_voidGoToXY(1, 0);
    LCD_voidSendString("1:Slw 2:Fst 3:Tr");

    while (G_ChargeMode == MODE_NONE)
    {
        key = KPD_u8GetPressedKey();

        if      (key == '1') { G_ChargeMode = MODE_SLOW;    }
        else if (key == '2') { G_ChargeMode = MODE_FAST;    }
        else if (key == '3') { G_ChargeMode = MODE_TRICKLE; }

        _delay_ms(50);
    }

    /* Confirm selected mode on LCD */
    LCD_voidClear();
    LCD_voidGoToXY(0, 0);
    LCD_voidSendString("Mode Selected:  ");
    LCD_voidGoToXY(1, 0);

    if      (G_ChargeMode == MODE_SLOW)    { LCD_voidSendString("  SLOW CHARGE   "); }
    else if (G_ChargeMode == MODE_FAST)    { LCD_voidSendString("  FAST CHARGE   "); }
    else if (G_ChargeMode == MODE_TRICKLE) { LCD_voidSendString("TRICKLE CHARGE  "); }

    _delay_ms(1500);
    LCD_voidClear();

    /* Start charging — enter BULK state */
    G_State = STATE_BULK;
    DIO_voidSetPinValue(CHARGER_PORT, CHARGER_PIN, HIGH);   /* Relay ON */

    while (1)
    {
        /*--------------------------------------------------------------------
         *  1) Check emergency disconnect
         *--------------------------------------------------------------------*/
        if (G_DisconnectFlag == 1u)
        {
            G_DisconnectFlag = 0u;
            G_State = STATE_DISCONNECT;
            DIO_voidSetPinValue(CHARGER_PORT, CHARGER_PIN, LOW);
            DIO_voidSetPinValue(ALARM_PORT,   ALARM_PIN,   HIGH);
            LCD_voidClear();
        }

        /*--------------------------------------------------------------------
         *  2) Read battery voltage and temperature from ADC
         *--------------------------------------------------------------------*/
        batADC  = ADC_u16ReadChannel(BAT_VOLT_CH);
        tempADC = ADC_u16ReadChannel(BAT_TEMP_CH);

        /*--------------------------------------------------------------------
         *  3) Over-voltage / Over-temperature protection
         *--------------------------------------------------------------------*/
        if ((G_State != STATE_ALARM)      &&
            (G_State != STATE_DISCONNECT) &&
            (G_State != STATE_IDLE)       &&
            (G_State != STATE_COMPLETE))
        {
            if ((batADC >= OVERVOLTAGE_ADC) || (tempADC >= OVERTEMP_ADC))
            {
                G_State = STATE_ALARM;
                DIO_voidSetPinValue(CHARGER_PORT, CHARGER_PIN, LOW);
                DIO_voidSetPinValue(ALARM_PORT,   ALARM_PIN,   HIGH);
                LCD_voidClear();
            }
        }

        /*--------------------------------------------------------------------
         *  4) State Machine
         *--------------------------------------------------------------------*/
        switch (G_State)
        {
            /*----------------------------------------------------------------
             *  IDLE: charger OFF — should not reach here normally
             *----------------------------------------------------------------*/
            case STATE_IDLE:
                DIO_voidSetPinValue(CHARGER_PORT, CHARGER_PIN, LOW);
                break;

            /*----------------------------------------------------------------
             *  BULK: full current charge until absorption voltage reached
             *----------------------------------------------------------------*/
            case STATE_BULK:
                if (batADC >= ABSORPTION_VOLT_ADC)
                {
                    G_State    = STATE_ABSORPTION;
                    G_AbsTimer = 0u;
                    LCD_voidClear();
                }
                break;

            /*----------------------------------------------------------------
             *  ABSORPTION: hold voltage for ABSORPTION_TIME_S seconds
             *----------------------------------------------------------------*/
            case STATE_ABSORPTION:
                if (G_SecondFlag == 1u)
                {
                    G_SecondFlag = 0u;
                    G_AbsTimer++;

                    if (G_AbsTimer >= ABSORPTION_TIME_S)
                    {
                        G_State      = STATE_FLOAT;
                        G_FloatTimer = 0u;
                        LCD_voidClear();
                    }
                }
                break;

            /*----------------------------------------------------------------
             *  FLOAT: reduced voltage maintenance
             *  Trickle mode => stay here forever
             *----------------------------------------------------------------*/
            case STATE_FLOAT:
                if (G_ChargeMode != MODE_TRICKLE)
                {
                    if (G_SecondFlag == 1u)
                    {
                        G_SecondFlag = 0u;
                        G_FloatTimer++;

                        if (G_FloatTimer >= FLOAT_TIME_S)
                        {
                            G_State = STATE_COMPLETE;
                            DIO_voidSetPinValue(CHARGER_PORT,  CHARGER_PIN,  LOW);
                            DIO_voidSetPinValue(COMPLETE_PORT, COMPLETE_PIN, HIGH);
                            LCD_voidClear();
                        }
                    }
                }
                /* Trickle mode: clear flag and stay in FLOAT */
                else
                {
                    G_SecondFlag = 0u;
                }
                break;

            /*----------------------------------------------------------------
             *  COMPLETE: charge done, relay OFF, complete LED ON
             *----------------------------------------------------------------*/
            case STATE_COMPLETE:
                /* Nothing to do — just display */
                break;

            /*----------------------------------------------------------------
             *  ALARM: over-voltage or over-temperature
             *  Auto-resume to BULK when condition clears
             *----------------------------------------------------------------*/
            case STATE_ALARM:
                if ((batADC < OVERVOLTAGE_ADC) && (tempADC < OVERTEMP_ADC))
                {
                    G_State = STATE_BULK;
                    DIO_voidSetPinValue(CHARGER_PORT, CHARGER_PIN, HIGH);
                    DIO_voidSetPinValue(ALARM_PORT,   ALARM_PIN,   LOW);
                    LCD_voidClear();
                }
                break;

            /*----------------------------------------------------------------
             *  DISCONNECT: emergency stop — stay here until reset
             *----------------------------------------------------------------*/
            case STATE_DISCONNECT:
                /* Stay here — user must power-cycle to recover */
                break;

            default:
                break;
        }

        /*--------------------------------------------------------------------
         *  5) Update LCD display
         *--------------------------------------------------------------------*/
        LCD_PrintState();
        LCD_voidGoToXY(1, 0);

        switch (G_State)
        {
            case STATE_ALARM:
                if (tempADC >= OVERTEMP_ADC)
                    { LCD_voidSendString("OVER-TEMP!      "); }
                else
                    { LCD_voidSendString("OVER-VOLTAGE!   "); }
                break;

            case STATE_DISCONNECT:
                LCD_voidSendString("Bat Disconnected");
                break;

            case STATE_COMPLETE:
                LCD_voidSendString("Charge Complete!");
                break;

            default:
                /* Show live voltage and temperature readings */
                LCD_PrintVoltage(batADC);
                LCD_voidSendString(" ");
                LCD_PrintTemp(tempADC);
                LCD_voidSendString("  ");
                break;
        }

        _delay_ms(300);   /* LCD refresh every 300ms */
    }

    return 0;
}
