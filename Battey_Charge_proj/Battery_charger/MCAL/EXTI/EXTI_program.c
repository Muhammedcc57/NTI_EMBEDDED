#include "Std_Types.h"
#include "Bit_Math.h"

#include "EXTI_private.h"
#include "EXTI_int.h"

#define NULL ((void *)0)


static void (*INT0_Callback)(void) = NULL;
static void (*INT1_Callback)(void) = NULL;
static void (*INT2_Callback)(void) = NULL;


void EXTI_voidInit(u8 IntID, u8 SenseControl) {
    if (IntID == EXTI_INT0) {
        switch(SenseControl) {
            case EXTI_LOW_LEVEL:    CLR_BIT(MCUCR, 0); CLR_BIT(MCUCR, 1); break;
            case EXTI_ON_CHANGE:    SET_BIT(MCUCR, 0); CLR_BIT(MCUCR, 1); break;
            case EXTI_FALLING_EDGE: CLR_BIT(MCUCR, 0); SET_BIT(MCUCR, 1); break;
            case EXTI_RISING_EDGE:  SET_BIT(MCUCR, 0); SET_BIT(MCUCR, 1); break;
        }
    } 
    else if (IntID == EXTI_INT1) {
        switch(SenseControl) {
            case EXTI_LOW_LEVEL:    CLR_BIT(MCUCR, 2); CLR_BIT(MCUCR, 3); break;
            case EXTI_ON_CHANGE:    SET_BIT(MCUCR, 2); CLR_BIT(MCUCR, 3); break;
            case EXTI_FALLING_EDGE: CLR_BIT(MCUCR, 2); SET_BIT(MCUCR, 3); break;
            case EXTI_RISING_EDGE:  SET_BIT(MCUCR, 2); SET_BIT(MCUCR, 3); break;
        }
    } 
    else if (IntID == EXTI_INT2) {
        
        switch(SenseControl) {
            case EXTI_FALLING_EDGE: CLR_BIT(MCUCSR, 6); break;
            case EXTI_RISING_EDGE:  SET_BIT(MCUCSR, 6); break;
        }
    }
}


void EXTI_voidEnable(u8 IntID) {
    switch(IntID) {
        case EXTI_INT0: SET_BIT(GICR, 6); break;
        case EXTI_INT1: SET_BIT(GICR, 7); break;
        case EXTI_INT2: SET_BIT(GICR, 5); break;
    }
}


void EXTI_voidDisable(u8 IntID) {
    switch(IntID) {
        case EXTI_INT0: CLR_BIT(GICR, 6); break;
        case EXTI_INT1: CLR_BIT(GICR, 7); break;
        case EXTI_INT2: CLR_BIT(GICR, 5); break;
    }
}


void EXTI_voidSetCallBack(u8 IntID, void (*func)(void)) {
    
    if(func != NULL) {
        if (IntID == EXTI_INT0) {
            INT0_Callback = func;
        } 
        else if (IntID == EXTI_INT1) {
            INT1_Callback = func;
        } 
        else if (IntID == EXTI_INT2) {
            INT2_Callback = func;
        }
    }
}



void __vector_1(void) __attribute__((signal));
void __vector_1(void) {
    if(INT0_Callback != NULL) {
        INT0_Callback();
    }
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void) {
    if(INT1_Callback != NULL) {
        INT1_Callback();
    }
}

void __vector_3(void) __attribute__((signal));
void __vector_3(void) {
    if(INT2_Callback != NULL) {
        INT2_Callback();
    }
}
