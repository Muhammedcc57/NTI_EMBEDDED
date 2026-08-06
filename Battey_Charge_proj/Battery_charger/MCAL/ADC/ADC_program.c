/*
*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ADC_program.c >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*   
*    Author : Mohammed Omera
*	 Layer : MCAL
*
*
*/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

void ADC_voidInit(void)
{

#if ADC_VREF == AVCC

    SET_BIT(ADMUX,REFS0);
    CLR_BIT(ADMUX,REFS1);

#else

    CLR_BIT(ADMUX,REFS0);
    CLR_BIT(ADMUX,REFS1);

#endif

    /* Right Adjust */
    CLR_BIT(ADMUX,ADLAR);

    /* Prescaler = 128 */
    SET_BIT(ADCSRA,0);
    SET_BIT(ADCSRA,1);
    SET_BIT(ADCSRA,2);

    /* Enable ADC */
    SET_BIT(ADCSRA,ADEN);
}


u16 ADC_u16ReadChannel(u8 Copy_u8Channel)
{
    u16 Local_u16Result;

    /* Select Channel */
    ADMUX &= 0b11100000;
    ADMUX |= Copy_u8Channel;

    /* Start Conversion */
    SET_BIT(ADCSRA,ADSC);

    /* Wait Until Finish */
    while(GET_BIT(ADCSRA,ADIF)==0);

    /* Clear Flag */
    SET_BIT(ADCSRA,ADIF);

    /* Read Result */

    Local_u16Result = ADCL;
    Local_u16Result |= (ADCH<<8);

    return Local_u16Result;
}