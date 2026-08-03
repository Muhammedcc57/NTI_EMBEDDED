/*
*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LCD_program.c >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*   
*    Author : Mohammed Omera
*	 Layer : HAL	
*
*
*/

/* Include Header Files */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include <util/delay.h>

#include "LCD_Interface.h"
#include "LCD_Private.h"
#include "LCD_Config.h"

/*****************************************************************************************/
/* Function Name : LCD_voidInit                                                          */
/* Description : Initializes the LCD                                                     */
/* Return : void                                                                         */
/*****************************************************************************************/
void LCD_voidInit(void)
{
	#if defined LCD_8BIT_MODE
	
	/* Configure Control Pins as Output */
	DIO_voidSetPortDirection(LCD_DATA_PORT, OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, RS_PIN, OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, RW_PIN, OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, E_PIN, OUTPUT);

	_delay_ms(35);

	/* Function Set Command */
	LCD_voidSendCommand(FS_8BIT_2LINES_5x7);
	_delay_ms(1);

	/* Display ON, Cursor ON */
	LCD_voidSendCommand(DIS_ON_CURSOR_ON);
	_delay_ms(1);

	/* Clear Display and Reset Cursor */
	LCD_voidClearDisplay();  // Clears display & ensures cursor at (0,0)
	_delay_ms(2);

	/* Entry Mode Set */
	LCD_voidSendCommand(ENTRY_MODE_INCREASE_NO_SHIFT);
	_delay_ms(1);
	
	#elif defined LCD_4BIT_MODE
	#if   defined LCD_4BIT_HIGHT_NIBBLE
	
	DIO_voidSetNibbleDirection(LCD_DATA_PORT,HIGH_NIBBLE,OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, RS_PIN, OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, RW_PIN, OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, E_PIN, OUTPUT);
	
	_delay_ms(35);
	
	/* Function Set Command */
	LCD_voidSendCommand(0x02);
	_delay_ms(1);
	LCD_voidSendCommand(FS_4BIT_2LINES_5x7);
	_delay_ms(1);

	/* Display ON, Cursor ON */
	LCD_voidSendCommand(DIS_ON_CURSOR_ON);
	_delay_ms(1);
	
	/* Clear Display and Reset Cursor */
	LCD_voidClearDisplay();  // Clears display & ensures cursor at (0,0)
	_delay_ms(2);

	/* Entry Mode Set */
	LCD_voidSendCommand(ENTRY_MODE_INCREASE_NO_SHIFT);
	_delay_ms(1);
	
	#elif defined LCD_4BIT_LOW_NIBBLE
	
	DIO_voidSetNibbleDirection(LCD_DATA_PORT,LOW_NIBBLE,OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, RS_PIN, OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, RW_PIN, OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, E_PIN, OUTPUT);
	
	_delay_ms(35);

	
	/* Function Set Command */
	LCD_voidSendCommand(0x02);
	_delay_ms(1);
	LCD_voidSendCommand(FS_4BIT_2LINES_5x7);
	_delay_ms(1);


	/* Display ON, Cursor ON */
	LCD_voidSendCommand(DIS_ON_CURSOR_OFF);
	_delay_ms(1);

	/* Clear Display and Reset Cursor */
	LCD_voidClearDisplay();  // Clears display & ensures cursor at (0,0)
	_delay_ms(2);

	/* Entry Mode Set */
	LCD_voidSendCommand(ENTRY_MODE_INCREASE_NO_SHIFT);
	_delay_ms(1);
	#endif
	#endif
	
	
}

/*****************************************************************************************/
/* Function Name : LCD_voidSendCommand                                                   */
/* Description : Sends a command to the LCD                                              */
/* Argument : Copy_u8Command (Command to send)                                           */
/* Return : void                                                                         */
/*****************************************************************************************/
void LCD_voidSendCommand(u8 Copy_u8Command)
{
	#if defined LCD_8BIT_MODE
	
	/* RS=0 for Command */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RS_PIN, LOW);

	/* RW=0 for Write */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RW_PIN, LOW);

	/* Send Command */
	DIO_voidSetPortValue(LCD_DATA_PORT, Copy_u8Command);

	/* Enable Pulse */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, LOW);
	_delay_ms(2);
	
	#elif defined LCD_4BIT_MODE
	#if   defined LCD_4BIT_HIGHT_NIBBLE
	
	/* RS=0 for Command */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RS_PIN, LOW);

	/* RW=0 for Write */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RW_PIN, LOW);

	/* Send Command HIGHT 4*/
	DIO_voidSetNibbleValue(LCD_DATA_PORT,HIGH_NIBBLE, Copy_u8Command >> 4);

	/* Enable Pulse */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, LOW);
	_delay_ms(2);
	
	///////////////////////////////////////////////////////////////
	
	/* RS=0 for Command */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RS_PIN, LOW);

	/* RW=0 for Write */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RW_PIN, LOW);

	/* Send Command  LOW 4*/
	DIO_voidSetNibbleValue(LCD_DATA_PORT,HIGH_NIBBLE, Copy_u8Command );

	/* Enable Pulse */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, LOW);
	_delay_ms(2);
	
	#elif defined LCD_4BIT_LOW_NIBBLE
	
	/* RS=0 for Command */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RS_PIN, LOW);

	/* RW=0 for Write */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RW_PIN, LOW);

	/* Send Command HIGHT 4 */
	DIO_voidSetNibbleValue(LCD_DATA_PORT,LOW_NIBBLE, Copy_u8Command >> 4);

	/* Enable Pulse */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, LOW);
	_delay_ms(2);
	
	///////////////////////////////////////////////////////////////
	
	/* RS=0 for Command */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RS_PIN, LOW);

	/* RW=0 for Write */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RW_PIN, LOW);

	/* Send Command LOW 4*/
	DIO_voidSetNibbleValue(LCD_DATA_PORT,LOW_NIBBLE, Copy_u8Command );

	/* Enable Pulse */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, LOW);
	_delay_ms(2);
	
	#endif
	#endif
	
}

/*****************************************************************************************/
/* Function Name : LCD_voidWriteChar                                                     */
/* Description : Writes a character to the LCD                                           */
/* Argument : Copy_u8Char (Character to display)                                         */
/* Return : void                                                                         */
/*****************************************************************************************/
void LCD_voidWriteChar(u8 Copy_u8Char)
{
	#if defined LCD_8BIT_MODE
	
	/* RS=1 for Data */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RS_PIN, HIGH);

	/* RW=0 for Write */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RW_PIN, LOW);

	/* Send Data */
	DIO_voidSetPortValue(LCD_DATA_PORT, Copy_u8Char);

	/* Enable Pulse */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, LOW);
	_delay_ms(2);
	
	#elif defined LCD_4BIT_MODE
	#if   defined LCD_4BIT_HIGHT_NIBBLE
	
	/* RS=1 for Data */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RS_PIN, HIGH);

	/* RW=0 for Write */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RW_PIN, LOW);

	/* Send Data HIGHT 4 */
	DIO_voidSetNibbleValue(LCD_DATA_PORT,HIGH_NIBBLE, Copy_u8Char >> 4);

	/* Enable Pulse */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, LOW);
	_delay_ms(2);
	
	///////////////////////////////////////////////////////////////
	
	/* RS=1 for Data */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RS_PIN, HIGH);

	/* RW=0 for Write */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RW_PIN, LOW);

	/* Send Data LOW 4*/
	DIO_voidSetNibbleValue(LCD_DATA_PORT,HIGH_NIBBLE, Copy_u8Char );

	/* Enable Pulse */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, LOW);
	_delay_ms(2);
	
	#elif defined LCD_4BIT_LOW_NIBBLE
	
	/* RS=1 for Data */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RS_PIN, HIGH);

	/* RW=0 for Write */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RW_PIN, LOW);

	/* Send Data HIGHT 4 */
	DIO_voidSetNibbleValue(LCD_DATA_PORT,LOW_NIBBLE, Copy_u8Char >> 4);

	/* Enable Pulse */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, LOW);
	_delay_ms(2);
	
	///////////////////////////////////////////////////////////////
	
	/* RS=1 for Data */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RS_PIN, HIGH);

	/* RW=0 for Write */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RW_PIN, LOW);

	/* Send Data LOW 4 */
	DIO_voidSetNibbleValue(LCD_DATA_PORT,LOW_NIBBLE, Copy_u8Char );

	/* Enable Pulse */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, E_PIN, LOW);
	_delay_ms(2);
	
	#endif
	#endif
}

/*****************************************************************************************/
/* Function Name : LCD_voidWriteString                                                   */
/* Description : Writes a string to the LCD                                              */
/* Argument : *Copy_u8Arr (Pointer to the string)                                        */
/* Return : void                                                                         */
/*****************************************************************************************/
void LCD_voidWriteString(u8 *Copy_u8Arr)
{
	u8 i = 0;
	while (Copy_u8Arr[i] != '\0')
	{
		LCD_voidWriteChar(Copy_u8Arr[i]);
		i++;
	}
}

/*****************************************************************************************/
/* Function Name : LCD_voidWrite_u32Number                                               */
/* Description : Writes an unsigned 32-bit number to the LCD                             */
/* Argument : Copy_u32Number (Number to display)                                         */
/* Return : void                                                                         */
/*****************************************************************************************/
void LCD_voidWrite_u32Number(u32 Copy_u32Number)
{
	u8 Arr[10];  // Maximum 10 digits
	u8 i = 0;

	if (Copy_u32Number == 0)
	{
		LCD_voidWriteChar('0');
		return;
	}

	while (Copy_u32Number > 0)
	{
		Arr[i++] = (Copy_u32Number % 10) + '0';
		Copy_u32Number /= 10;
	}

	for (s8 j = i - 1; j >= 0; j--)
	{
		LCD_voidWriteChar(Arr[j]);
	}
}

/*****************************************************************************************/
/* Function Name : LCD_voidGoTo_XY                                                       */
/* Description : Moves the cursor to a specific row and column                           */
/* Arguments : Copy_u8Line (LINE_1, LINE_2), Copy_u8Position (0-15)                      */
/* Return : void                                                                         */
/*****************************************************************************************/
void LCD_voidGoTo_XY(u8 Copy_u8Line, u8 Copy_u8Position)
{
	if (Copy_u8Line > LINE_2 || Copy_u8Position > 15)
	{
		return;
	}
	else
	{
		switch (Copy_u8Line)
		{
			case LINE_1: LCD_voidSendCommand(0x80 + Copy_u8Position); _delay_ms(100);  break;
			case LINE_2: LCD_voidSendCommand(0xC0 + Copy_u8Position);  _delay_ms(100); break;
			default: break;
		}
	}
}

/*****************************************************************************************/
/* Function Name : LCD_voidDrawPattern                                                   */
/* Description : Saves a custom pattern in CGRAM                                         */
/* Arguments : Copy_u8Pattern_Number (0-7), *Copy_u8Arr_Pattern (Pattern data)           */
/* Return : void                                                                         */
/*****************************************************************************************/
void LCD_voidDrawPattern(u8 Copy_u8Pattern_Address, u8 *Copy_u8Arr_Pattern)
{
	LCD_voidSendCommand(0x40 + (Copy_u8Pattern_Address * 8)); // Set CGRAM Address

	for (u8 i = 0; i < 8; i++)
	{
		LCD_voidWriteChar(Copy_u8Arr_Pattern[i]);
	}
	_delay_ms(100);
}

/*****************************************************************************************/
/* Function Name : LCD_voidShowPattern                                                  */
/* Description : Displays a stored pattern on the LCD                                    */
/* Arguments : Copy_u8Pattern (0-7), Copy_u8Line, Copy_u8Position                        */
/* Return : void                                                                         */
/*****************************************************************************************/
void LCD_voidShowPattern(u8 Copy_u8Pattern, u8 Copy_u8Line, u8 Copy_u8Position)
{
	LCD_voidGoTo_XY(Copy_u8Line, Copy_u8Position); //  set DDRAM Address
	LCD_voidWriteChar(Copy_u8Pattern);
}

/*****************************************************************************************/
/* Function Name : LCD_voidClearDisplay                                                  */
/* Description : Clears the entire LCD display                                           */
/* Return : void                                                                         */
/*****************************************************************************************/
void LCD_voidClearDisplay(void)
{
	LCD_voidSendCommand(CLEAR_DIS);
	_delay_ms(2); 
	LCD_voidSendCommand(RETURN_HOME);  // cursor returns to position 0
	_delay_ms(2);
}

/*****************************************************************************************/
/* Function Name : LCD_voidShiftLeft                                                     */
/* Description : Shifts the entire LCD display left                                      */
/* Return : void                                                                         */
/*****************************************************************************************/
void LCD_voidShiftLeft(void)
{
	LCD_voidSendCommand(DIS_SHIFT_LEFT);
}

/*****************************************************************************************/
/* Function Name : LCD_voidShiftRight                                                    */
/* Description : Shifts the entire LCD display right                                     */
/* Return : void                                                                         */
/*****************************************************************************************/
void LCD_voidShiftRight(void)
{
	LCD_voidSendCommand(DIS_SHIFT_RIGHT);
}

/*****************************************************************************************/
/* Function Name : LCD_voidClearGrid                                                     */
/* Description : Clears a specific character position on the LCD                         */
/* Arguments : Copy_u8Line, Copy_u8Position                                              */
/* Return : void                                                                         */
/*****************************************************************************************/
void LCD_voidClearGrid(u8 Copy_u8Line, u8 Copy_u8Position)
{
	LCD_voidGoTo_XY(Copy_u8Line, Copy_u8Position);
	LCD_voidWriteChar(' ');
}

/*****************************************************************************************/
/* Function Name : LCD_voidClearLine                                                     */
/* Description : Clears an entire line on the LCD                                        */
/* Argument : Copy_u8Line                                                                */
/* Return : void                                                                         */
/*****************************************************************************************/
void LCD_voidClearLine(u8 Copy_u8Line)
{
	for (u8 i = 0; i < 16; i++)
	{
		LCD_voidGoTo_XY(Copy_u8Line, i);
		LCD_voidWriteChar(' ');
	}
}

void LCD_voidRETURN_HOME ()
{
	LCD_voidSendCommand(RETURN_HOME);  // cursor returns to position 0
	_delay_ms(100);
}