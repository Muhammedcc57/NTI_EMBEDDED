

#ifndef LCD_PRIVATE_H
#define LCD_PRIVATE_H

/*==========================
        LCD Commands
===========================*/

/* Clear Display */
#define LCD_CLEAR_DISPLAY          0x01

/* Return Cursor Home */
#define LCD_RETURN_HOME            0x02

/* Entry Mode */
#define LCD_ENTRY_MODE             0x06

/* Display ON - Cursor OFF */
#define LCD_DISPLAY_ON             0x0C

/* Display ON - Cursor ON */
#define LCD_DISPLAY_CURSOR_ON      0x0E

/* Display ON - Cursor Blink */
#define LCD_DISPLAY_CURSOR_BLINK   0x0F

/* Function Set */
#define LCD_8BIT_MODE              0x38
#define LCD_4BIT_MODE              0x28

/* Cursor Addresses */
#define LCD_FIRST_LINE             0x80
#define LCD_SECOND_LINE            0xC0

#endif