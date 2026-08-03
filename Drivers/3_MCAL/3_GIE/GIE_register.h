/*
*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< GIE_register.h >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*   
*    Author : Mohammed Omera
*	 Layer : MCAL
*
*
*/


#ifndef GIE_REGISTER_H_
#define GIE_REGISTER_H_

	#define SREG			*((volatile u8*) 0X5F)	/* Status Register */
	#define SREG_I			7							/* Global Interrupt Enable Bit */

#endif /* GIE_REGISTER_H_ */