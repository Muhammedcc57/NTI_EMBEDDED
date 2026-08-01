/*
*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< DIO_program.c >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*   
*    Author : Mohammed Omera
*	 Layer : MCAL	
*
*
*/

#include "Std_Types.h"
#include "Bit_Math.h"

#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"

void DIO_voidInitialization(void)
{
	DDRA = DIO_PORTA_DIRECTIONS;
	DDRB = DIO_PORTB_DIRECTIONS;
	DDRC = DIO_PORTC_DIRECTIONS;
	DDRD = DIO_PORTD_DIRECTIONS;
}

void   DIO_voidSetPinDirection(u8 PortID, u8 PinID, u8 Direction)
{
	if(PortID < 4 && PinID < 8)
	{
		if(Direction == OUTPUT)
		{
			switch(PortID)
			{
				case PORTA: SET_BIT(DDRA, PinID); break;
				case PORTB: SET_BIT(DDRB, PinID); break;
				case PORTC: SET_BIT(DDRC, PinID); break;
				case PORTD: SET_BIT(DDRD, PinID); break;
			}
		}
		else if(Direction == INPUT)
		{
			switch(PortID)
			{
				case PORTA: CLR_BIT(DDRA, PinID); break;
				case PORTB: CLR_BIT(DDRB, PinID); break;
				case PORTC: CLR_BIT(DDRC, PinID); break;
				case PORTD: CLR_BIT(DDRD, PinID); break;
			}
		}
		else
		{
			
			/** thiselse for any valye not input or output */
		}
	}
	else
	{
		// No Code
	}
}

#define GET_BIT(REG, BITNUM)   		((REG>>BITNUM)&0x01)
#define TOGGLE_BIT(REG, BITNUM)		(REG ^=1<<BITNUM)
#define SET_BYTE(REG, VALUE)		REG=VALUE

#define CONC_BIT(b7,b6,b5,b4,b3,b2,b1,b0) 0b##b7##b6##b5##b4##b3##b2##b1##b0
 
/** Output Mode */
void DIO_voidSetpinValue(u8 PortID,u8 PinID, u8 Value)
{
	
	
}


/** Input Mode*/
u8 DIO_u8GetPinValue(u8 PortID, u8 PinID)
{
	
}



/** Output Mode */
void DIO_voidTogglePin(u8 PortID, u8 PinID)
{
	
}
/** output - input*/
void DIO_voidSetPortDirection(u8 PortID, u8 Direction);


/** High - Low*/
void DIO_voidSetPortValue(u8 PortID, u8 Value);
