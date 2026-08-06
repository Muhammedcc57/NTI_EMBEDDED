
/*
 * main.c
 * LM35 Temperature Sensor Display on LCD
 * Author : Mohammed Omera
 * MCU    : ATmega32
 * LCD    : 8-bit mode
 * LM35   : ADC Channel 0 (PA0)
 */

#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "ADC_interface.h"
#include "CLCD_interface.h"

int main(void)
{
    /* ── Variables ── */
    u16 ADC_Value   = 0;   /* Stores raw ADC reading (0 - 1023)       */
    u16 Temperature = 0;   /* Stores calculated temperature in Celsius */

    /* ── Driver Initialization ── */
    ADC_voidInit();        /* Initialize ADC peripheral  */
    CLCD_voidInit();       /* Initialize LCD display     */

    /* ── Welcome Message ── */
    CLCD_voidSetPosition(CLCD_ROW_1, CLCD_COL_1);
    CLCD_voidSendString((const u8 *)"  Temp Monitor  ");
    CLCD_voidSetPosition(CLCD_ROW_2, CLCD_COL_1);
    CLCD_voidSendString((const u8 *)" NTI Simulation ");
    _delay_ms(2000);       /* Display welcome message for 2 seconds */
    CLCD_voidClearScreen();

    /* ── Static Title on Row 1 ── */
    CLCD_voidSetPosition(CLCD_ROW_1, CLCD_COL_1);
    CLCD_voidSendString((const u8 *)"  Temperature:  ");

    while(1)
    {
        /* ── Step 1: Read ADC value from Channel 0 (LM35 output) ── */
        ADC_Value = ADC_u16ReadChannel(ADC_CHANNEL0);

        /*
         * ── Step 2: Convert ADC reading to Temperature ──
         *
         * Formula:
         *   VREF        = 5000 mV
         *   Resolution  = 1024 steps
         *   Voltage(mV) = ADC_Value x (5000 / 1024)
         *               = ADC_Value x 4.887
         *
         *   LM35 outputs 10mV per degree Celsius
         *   Temperature = Voltage / 10
         *               = (ADC_Value x 4887) / 10000
         *
         * Example:
         *   ADC_Value = 51  =>  Voltage = 249 mV  =>  Temperature = 24 C
         */
        Temperature = (u16)((u32)(ADC_Value * 4887UL) / 10000UL);

        /* ── Step 3: Display temperature value on Row 2 ── */
        CLCD_voidSetPosition(CLCD_ROW_2, CLCD_COL_4);
        CLCD_voidSendNumber(Temperature);          /* Send temperature digits */
        CLCD_voidSendString((const u8 *)" C  ");   /* Send unit label         */

        /* ── Step 4: Wait 500ms before next reading ── */
        _delay_ms(500);
    }

    return 0;
}
