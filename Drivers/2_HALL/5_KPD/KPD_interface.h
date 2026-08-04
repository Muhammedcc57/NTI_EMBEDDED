/*
*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< KPD_interface.h >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*   
*    Author : Mohammed Omera
*	 Layer : HAL	
*
*
*/


#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_

#define NOTPRESSED 0xff

void KPD_Init(void);
u8   KPD_u8GetPressed( void );

#endif /* KPD_INTERFACE_H_ */