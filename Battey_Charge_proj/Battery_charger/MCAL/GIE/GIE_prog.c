#include "Std_Types.h"
#include "Bit_Math.h"

#include "GIE_int.h"
#include "GIE_register.h"


void GIE_VoidEnable (void)
{
	SET_BIT(SREG , SREG_I);
}

void GIE_VoidDisable (void)
{
	CLR_BIT(SREG , SREG_I);
}