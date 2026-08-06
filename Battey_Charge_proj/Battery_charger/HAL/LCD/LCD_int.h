#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#include "STD_TYPES.h"

/* Initialization */
void LCD_voidInit(void);

/* Commands & Data */
void LCD_voidSendCommand(u8 Copy_u8Command);
void LCD_voidSendData(u8 Copy_u8Data);

/* Display Functions */
void LCD_voidSendString(const char *Copy_pu8String);
void LCD_voidClear(void);

/* Cursor Functions */
void LCD_voidGoToXY(u8 Copy_u8Row, u8 Copy_u8Col);

/* Numbers */
void LCD_voidSendNumber(s32 Copy_s32Number);

#endif