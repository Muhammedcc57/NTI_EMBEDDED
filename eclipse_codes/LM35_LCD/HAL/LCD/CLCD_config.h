/*
*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< LCD_config.h >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*   
*    Author : Mohammed Omera
*	 Layer : HAL	
*
*
*/


/* File Gaurd by ifndef & endif */


#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

/***************************************************************************************/
/* LCD Mode */

	/* Choose 8 for 8_bit connection*/


#define CLCD_MODE  4


/* D0 ------> D7 */

/***************************************************************************************/


#define CLCD_DATA_PORT      DIO_PORTA
/* RS,RW,EN */
#define CLCD_CONTROL_PORT   DIO_PORTB

/***************************************************************************************/



#define CLCD_RS             DIO_PIN1
#define CLCD_RW             DIO_PIN2
#define CLCD_EN             DIO_PIN3

/***************************************************************************************/


#endif /* CLCD_CONFIG_H_ */