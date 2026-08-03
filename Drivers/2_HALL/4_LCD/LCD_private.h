/*
*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LCD_private.h >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*   
*    Author : Mohammed Omera
*	 Layer : HAL	
*
*
*/




/* File Gaurd by ifndef & endif */
#ifndef LCD_PRIVATE_H
#define LCD_PRIVATE_H

/* Private Macros */
/* LCD Function Set Commands */
#define   FS_8BIT_2LINES_5x10               0b00111100   // 8-bit mode, 2 lines, 5x10 font
#define   FS_4BIT_2LINES_5x10               0b00101100   // 4-bit mode, 2 lines, 5x10 font
#define   FS_8BIT_2LINES_5x7                0b00111000   // 8-bit mode, 2 lines, 5x7 font
#define   FS_4BIT_2LINES_5x7                0b00101000   // 4-bit mode, 2 lines, 5x7 font

/* LCD Display Control Commands */
#define   DIS_ON_CURSOR_OFF                 0b00001100   // Display ON, Cursor OFF
#define   DIS_OFF_CURSOR_OFF                0b00001000   // Display OFF, Cursor OFF
#define   DIS_ON_CURSOR_ON                  0b00001110   // Display ON, Cursor ON (No Blinking)
#define   DIS_ON_BLINKING_CURSOR            0b00001111   // Display ON, Cursor ON, Blinking

/* LCD Display Operations */
#define   CLEAR_DIS                         0b00000001   // Clear Display
#define   RETURN_HOME                       0b00000010   // Return Cursor to Home Position

/* LCD Entry Mode Set */
#define   ENTRY_MODE_INCREASE_SHIFT_LEFT    0b00000111   // Increment & Shift Left
#define   ENTRY_MODE_INCREASE_NO_SHIFT      0b00000110   // Increment & No Shift
#define   ENTRY_MODE_DECREASE_SHIFT_RIGHT   0b00000101   // Decrement & Shift Right
#define   ENTRY_MODE_DECREASE_NO_SHIFT      0b00000100   // Decrement & No Shift

/* LCD Cursor and Display Shift */
#define   CURSOR_SHIFT_LEFT                 0b00010000   // Move Cursor Left (AC - 1)
#define   CURSOR_SHIFT_RIGHT                0b00010100   // Move Cursor Right (AC + 1)
#define   DIS_SHIFT_LEFT                    0b00011000   // Shift Entire Display Left
#define   DIS_SHIFT_RIGHT                   0b00011100   // Shift Entire Display Right

           
#endif