/*
*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ADC_private.h >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*   
*    Author : Mohammed Omera
*	 Layer : MCAL
*
*
*/

#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

/* Registers */

#define ADMUX   *((volatile u8*)0x27)
#define ADCSRA  *((volatile u8*)0x26)
#define ADCL    *((volatile u8*)0x24)
#define ADCH    *((volatile u8*)0x25)

/* ADMUX Bits */
#define REFS0   6
#define REFS1   7
#define ADLAR   5

/* ADCSRA Bits */
#define ADEN    7
#define ADSC    6
#define ADIF    4

/* Voltage Reference */
#define AREF    0
#define AVCC    1

#endif