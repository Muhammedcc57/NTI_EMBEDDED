/*
*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< SW_program.c >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*   
*    Author : Mohammed Omera
*	 Layer : HAL	
*
*
*/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include <util\delay.h>

#include "DIO_interface.h"


#include "SW_interface.h"
#include "SW_private.h"
#include "SW_config.h"


void SW_voidInit      ( SW_Type SW_Config ){
	
	DIO_enumSetPinDirection( SW_Config.Port , SW_Config.Pin , DIO_PIN_INPUT );
	
	/* If Sw is Internal Pull Up */
	if( SW_Config.Pull_State == SW_Int_PULL_UP ){
		
		DIO_enumSetPinValue    ( SW_Config.Port , SW_Config.Pin , DIO_PIN_HIGH  );
		
		/* we could use DIO_enumConnectPullup */
	}
	
}

u8   SW_u8GetPressed ( SW_Type SW_Config ){
	
	u8 LOC_u8Result = SW_NOT_PRESSED ;
	u8 LOC_u8PinVal = SW_NOT_PRESSED ;
	
	if ( (SW_Config.Pull_State == SW_Int_PULL_UP) || (SW_Config.Pull_State == SW_Ext_PULL_UP) )
	{
		DIO_enumGetPinValue( SW_Config.Port , SW_Config.Pin , &LOC_u8PinVal );
		
		if (LOC_u8PinVal==0)
		{
			LOC_u8Result = SW_PRESSED ;
		}
		else if (LOC_u8PinVal==1)
		{
			LOC_u8Result = SW_NOT_PRESSED ;
		}

	}
	else if (SW_Config.Pull_State == SW_Ext_PULL_DOWN)
	{
		DIO_enumGetPinValue( SW_Config.Port , SW_Config.Pin , &LOC_u8PinVal );
		
		if (LOC_u8PinVal==0)
		{
			LOC_u8Result = SW_NOT_PRESSED ;
		}
		else if (LOC_u8PinVal==1)
		{
			LOC_u8Result = SW_PRESSED ;
		}
	}
		
	return LOC_u8Result ;
	
}
