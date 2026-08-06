#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

#include "Std_Types.h"


#define EXTI_INT0   0
#define EXTI_INT1   1
#define EXTI_INT2   2


#define EXTI_LOW_LEVEL      0
#define EXTI_ON_CHANGE      1
#define EXTI_FALLING_EDGE   2
#define EXTI_RISING_EDGE    3


void EXTI_voidInit(u8 IntID, u8 SenseControl);


void EXTI_voidEnable(u8 IntID);


void EXTI_voidDisable(u8 IntID);


void EXTI_voidSetCallBack(u8 IntID, void (*func)(void));

#endif