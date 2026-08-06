#include "STD_Types.h"
#include "BIT_Math.h"

#include "DIO_int.h"

#include "KPD_int.h"
#include "KPD_config.h"
#include "KPD_private.h"

static const u8 KPD_u8Keys[KPD_ROWS_NUM][KPD_COLS_NUM] = KPD_KEYS;

void KPD_voidInit(void)
{
    /* Rows Input Pull-Up */

    DIO_voidSetPinDirection(KPD_R0, INPUT);
    DIO_voidSetPinDirection(KPD_R1, INPUT);
    DIO_voidSetPinDirection(KPD_R2, INPUT);
    DIO_voidSetPinDirection(KPD_R3, INPUT);

    DIO_voidSetPinValue(KPD_R0, HIGH);
    DIO_voidSetPinValue(KPD_R1, HIGH);
    DIO_voidSetPinValue(KPD_R2, HIGH);
    DIO_voidSetPinValue(KPD_R3, HIGH);

    /* Columns Output */

    DIO_voidSetPinDirection(KPD_C0, OUTPUT);
    DIO_voidSetPinDirection(KPD_C1, OUTPUT);
    DIO_voidSetPinDirection(KPD_C2, OUTPUT);
    DIO_voidSetPinDirection(KPD_C3, OUTPUT);

    DIO_voidSetPinValue(KPD_C0, HIGH);
    DIO_voidSetPinValue(KPD_C1, HIGH);
    DIO_voidSetPinValue(KPD_C2, HIGH);
    DIO_voidSetPinValue(KPD_C3, HIGH);
}

u8 KPD_u8GetPressedKey(void)
{
    u8 Local_u8PressedKey = KPD_NOT_PRESSED;
    u8 Local_u8Row;
    u8 Local_u8Col;
    u8 Local_u8PinValue;

    for(Local_u8Col = 0 ; Local_u8Col < KPD_COLS_NUM ; Local_u8Col++)
    {
        /* Make all columns HIGH */

        DIO_voidSetPinValue(KPD_C0,HIGH);
        DIO_voidSetPinValue(KPD_C1,HIGH);
        DIO_voidSetPinValue(KPD_C2,HIGH);
        DIO_voidSetPinValue(KPD_C3,HIGH);

        /* Make current column LOW */

        switch(Local_u8Col)
        {
            case 0: DIO_voidSetPinValue(KPD_C0,LOW); break;
            case 1: DIO_voidSetPinValue(KPD_C1,LOW); break;
            case 2: DIO_voidSetPinValue(KPD_C2,LOW); break;
            case 3: DIO_voidSetPinValue(KPD_C3,LOW); break;
        }

        for(Local_u8Row = 0 ; Local_u8Row < KPD_ROWS_NUM ; Local_u8Row++)
        {
            switch(Local_u8Row)
            {
                case 0:
                    Local_u8PinValue = DIO_u8GetPinValue(KPD_R0);
                    break;

                case 1:
                    Local_u8PinValue = DIO_u8GetPinValue(KPD_R1);
                    break;

                case 2:
                    Local_u8PinValue = DIO_u8GetPinValue(KPD_R2);
                    break;

                case 3:
                    Local_u8PinValue = DIO_u8GetPinValue(KPD_R3);
                    break;
            }

            if(Local_u8PinValue == LOW)
            {
                Local_u8PressedKey = KPD_u8Keys[Local_u8Row][Local_u8Col];

                /* Wait until key released */

                while(Local_u8PinValue == LOW)
                {
                    switch(Local_u8Row)
                    {
                        case 0:
                            Local_u8PinValue = DIO_u8GetPinValue(KPD_R0);
                            break;

                        case 1:
                            Local_u8PinValue = DIO_u8GetPinValue(KPD_R1);
                            break;

                        case 2:
                            Local_u8PinValue = DIO_u8GetPinValue(KPD_R2);
                            break;

                        case 3:
                            Local_u8PinValue = DIO_u8GetPinValue(KPD_R3);
                            break;
                    }
                }

                return Local_u8PressedKey;
            }
        }
    }

    return KPD_NOT_PRESSED;
}

