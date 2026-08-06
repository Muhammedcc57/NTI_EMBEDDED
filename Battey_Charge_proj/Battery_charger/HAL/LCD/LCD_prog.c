#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_int.h"

#include "LCD_int.h"
#include "LCD_config.h"
#include "LCD_private.h"

#include <util/delay.h>


void LCD_voidInit(void)
{
	/* Set Data Port as Output */
	DIO_voidSetPortDirection(LCD_DATA_PORT, 0xFF);

	/* Set Control Pins as Output */
	DIO_voidSetPinDirection(LCD_RS_PORT, LCD_RS_PIN, OUTPUT);
	DIO_voidSetPinDirection(LCD_RW_PORT, LCD_RW_PIN, OUTPUT);
	DIO_voidSetPinDirection(LCD_EN_PORT, LCD_EN_PIN, OUTPUT);


	/* LCD Initialization Sequence */
	_delay_ms(30);

	LCD_voidSendCommand(LCD_8BIT_MODE);
	_delay_ms(5);

	LCD_voidSendCommand(LCD_DISPLAY_ON);
	_delay_ms(5);

	LCD_voidSendCommand(LCD_CLEAR_DISPLAY);
	_delay_ms(5);

	LCD_voidSendCommand(LCD_ENTRY_MODE);
}



void LCD_voidSendCommand(u8 Copy_u8Command)
{
	/* RS = 0 (Command) */
	DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, LOW);

	/* RW = 0 (Write) */
	DIO_voidSetPinValue(LCD_RW_PORT, LCD_RW_PIN, LOW);


	/* Put Command on Data Bus */
	DIO_voidSetPortValue(LCD_DATA_PORT, Copy_u8Command);


	/* Enable Pulse */
	DIO_voidSetPinValue(LCD_EN_PORT, LCD_EN_PIN, HIGH);
	_delay_ms(1);

	DIO_voidSetPinValue(LCD_EN_PORT, LCD_EN_PIN, LOW);

	_delay_ms(2);
}



void LCD_voidSendData(u8 Copy_u8Data)
{
	/* RS = 1 (Data) */
	DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, HIGH);

	/* RW = 0 (Write) */
	DIO_voidSetPinValue(LCD_RW_PORT, LCD_RW_PIN, LOW);


	/* Put Data on Data Bus */
	DIO_voidSetPortValue(LCD_DATA_PORT, Copy_u8Data);


	/* Enable Pulse */
	DIO_voidSetPinValue(LCD_EN_PORT, LCD_EN_PIN, HIGH);
	_delay_ms(1);

	DIO_voidSetPinValue(LCD_EN_PORT, LCD_EN_PIN, LOW);

	_delay_ms(2);
}



void LCD_voidSendString(const char *Copy_pu8String)
{
	u8 Local_u8Counter = 0;

	while(Copy_pu8String[Local_u8Counter] != '\0')
	{
		LCD_voidSendData(Copy_pu8String[Local_u8Counter]);

		Local_u8Counter++;
	}
}



void LCD_voidClear(void)
{
	LCD_voidSendCommand(LCD_CLEAR_DISPLAY);

	_delay_ms(2);
}



void LCD_voidGoToXY(u8 Copy_u8Row, u8 Copy_u8Col)
{
	u8 Local_u8Address;

	if(Copy_u8Row == 0)
	{
		Local_u8Address = LCD_FIRST_LINE + Copy_u8Col;
	}
	else
	{
		Local_u8Address = LCD_SECOND_LINE + Copy_u8Col;
	}

	LCD_voidSendCommand(Local_u8Address);
}



void LCD_voidSendNumber(s32 Copy_s32Number)
{
	char Local_chNumber[16];

	sprintf(Local_chNumber, "%ld", Copy_s32Number);

	LCD_voidSendString(Local_chNumber);
}
