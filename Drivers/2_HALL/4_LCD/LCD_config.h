/*
*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LCD_config.h >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*   
*    Author : Mohammed Omera
*	 Layer : HAL	
*
*
*/


/* File Gaurd by ifndef & endif */
#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H

#define LCD_4BIT_MODE
//#define LCD_4BIT_HIGHT_NIBBLE
#define LCD_4BIT_LOW_NIBBLE
//#define LCD_8BIT_MODE

/* LCD Hardware Configration with atmega PORTS & PINS */
#define LCD_DATA_PORT            PORTA

#define LCD_CONTROL_PORT         PORTA
#define RS_PIN                   PIN6
#define RW_PIN                   PIN5
#define E_PIN                    PIN4


#endif