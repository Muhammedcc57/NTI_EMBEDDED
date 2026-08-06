#include "STD_TYPES.h"
#include "Bit_Math.h"

#include "TIM0_private.h"
#include "TIM0_config.h"
#include "TIM0_int.h"

pf FunctionAddress1 = 0;
pf FunctionAddress2 = 0;
u8 TIM0_MODE;
u8 TIM0_PRESCALER;
u8 TIM0_PWM_MODE;
void TIM0_voidInit(void)
{
	CLR_BIT(TIMSK, 0);
	CLR_BIT(TIMSK, 1);

	SET_BIT(TIFR, 0);
	SET_BIT(TIFR, 1);

	TCNT0 = 0;
	OCR0  = 0;

	if (TIM0_MODE == NORMAL_MODE)
	{
		CLR_BIT(TCCR0, 6);
		CLR_BIT(TCCR0, 3);
		CLR_BIT(TCCR0, 4);
		CLR_BIT(TCCR0, 5);
	}

	if (TIM0_MODE == CTC_MODE)
	{
		CLR_BIT(TCCR0, 6);
		SET_BIT(TCCR0, 3);
		CLR_BIT(TCCR0, 4);
		CLR_BIT(TCCR0, 5);
	}

	if (TIM0_MODE == FAST_PWM_MODE)
	{
		SET_BIT(TCCR0, 6);
		SET_BIT(TCCR0, 3);

		SET_BIT(DDRB, 3);
		if (TIM0_PWM_MODE == PWM_NON_INVERTING)
			{
				CLR_BIT(TCCR0, 4);
				SET_BIT(TCCR0, 5);
			}

			if (TIM0_PWM_MODE == PWM_INVERTING)
			{
				SET_BIT(TCCR0, 4);
				SET_BIT(TCCR0, 5);
			}
	}

	if (TIM0_PRESCALER == NO_CLOCK)
	{
		CLR_BIT(TCCR0, 0);
		CLR_BIT(TCCR0, 1);
		CLR_BIT(TCCR0, 2);
	}

	if (TIM0_PRESCALER == PRESCALER_1)
	{
		SET_BIT(TCCR0, 0);
		CLR_BIT(TCCR0, 1);
		CLR_BIT(TCCR0, 2);
	}

	if (TIM0_PRESCALER == PRESCALER_8)
	{
		CLR_BIT(TCCR0, 0);
		SET_BIT(TCCR0, 1);
		CLR_BIT(TCCR0, 2);
	}

	if (TIM0_PRESCALER == PRESCALER_64)
	{
		SET_BIT(TCCR0, 0);
		SET_BIT(TCCR0, 1);
		CLR_BIT(TCCR0, 2);
	}

	if (TIM0_PRESCALER == PRESCALER_256)
	{
		CLR_BIT(TCCR0, 0);
		CLR_BIT(TCCR0, 1);
		SET_BIT(TCCR0, 2);
	}

	if (TIM0_PRESCALER == PRESCALER_1024)
	{
		SET_BIT(TCCR0, 0);
		CLR_BIT(TCCR0, 1);
		SET_BIT(TCCR0, 2);
	}
}

void TIM0_voidEnableOVInterrupt(void)
{
	SET_BIT(TIMSK, 0);
}

void TIM0_voidDisableOVInterrupt(void)
{
	CLR_BIT(TIMSK, 0);
}

void TIM0_voidSetOVReg(u8 u8OVRegValue)
{
	TCNT0 = u8OVRegValue;
}

u8 TIM0_u8ReadOVReg(void)
{
	return TCNT0;
}

void TIM0_voidOVSetCallBack(pf OVFunctionAddress)
{
	FunctionAddress1 = OVFunctionAddress;
}

void __vector_11(void) __attribute__((signal, used));
void __vector_11(void)
{
	if (FunctionAddress1 != 0)
	{
		FunctionAddress1();
	}
}

void TIM0_voidEnableCTCInterrupt(void)
{
	SET_BIT(TIMSK, 1);
}

void TIM0_voidDisableCTCInterrupt(void)
{
	CLR_BIT(TIMSK, 1);
}

void TIM0_voidSetCTCReg(u8 u8CTCRegValue)
{
	OCR0 = u8CTCRegValue;
}

u8 TIM0_u8ReadCTCReg(void)
{
	return OCR0;
}

void TIM0_voidCTCSetCallBack(pf CTCFunctionAddress)
{
	FunctionAddress2 = CTCFunctionAddress;
}

void __vector_10(void) __attribute__((signal, used));
void __vector_10(void)
{
	if (FunctionAddress2 != 0)
	{
		FunctionAddress2();
	}
}

