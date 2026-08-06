/*
*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ADC_interface.h >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*   
*    Author : Mohammed Omera
*	 Layer : MCAL
*
*
*/

#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#include "STD_TYPES.h"

/* ADC Channels */
#define ADC_CHANNEL0    0
#define ADC_CHANNEL1    1
#define ADC_CHANNEL2    2
#define ADC_CHANNEL3    3
#define ADC_CHANNEL4    4
#define ADC_CHANNEL5    5
#define ADC_CHANNEL6    6
#define ADC_CHANNEL7    7

void ADC_voidInit(void);

u16 ADC_u16ReadChannel(u8 Copy_u8Channel);

#endif