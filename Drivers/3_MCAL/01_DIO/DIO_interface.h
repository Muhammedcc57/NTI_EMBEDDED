/*
*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< DIO_interface.h >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*   
*    Author : Mohammed Omera
*	 Layer : MCAL	
*
*
*/

#ifndef   DIO_INTERFACE_H_
#define   DIO_INTERFACE_H_

 
 
 
// Port Defines
#define  DIO_PORTA  0
#define  DIO_PORTB  1
#define  DIO_PORTC  2
#define  DIO_PORTD  3


// PIN Defines
#define DIO_PIN0   0
#define DIO_PIN1   1
#define DIO_PIN2   2
#define DIO_PIN3   3
#define DIO_PIN4   4
#define DIO_PIN5   5
#define DIO_PIN6   6
#define DIO_PIN7   7

#define OUTPUT     1
#define INPUT      0

#define LOW        0
#define HIGH       1

void DIO_voidInitialization(void);
void   DIO_voidSetPinDirection(u8 PortID, u8 PinID, u8 Direction);

#endif