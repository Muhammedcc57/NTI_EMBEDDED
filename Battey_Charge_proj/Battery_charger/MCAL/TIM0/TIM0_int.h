#ifndef TIM0_INT_H
#define TIM0_INT_H

#include "STD_TYPES.h"
/*  TCCR0 */
#define FOC0  7
#define WGM00 6
#define COM01 5
#define COM00 4
#define WGM01 3
#define CS02  2
#define CS01  1
#define CS00  0

/*  TIMSK  */
#define OCIE2  7
#define TOIE2  6
#define TICIE1 5
#define OCIE1A 4
#define OCIE1B 3
#define TOIE1  2
#define OCIE0  1
#define TOIE0  0

/*  TIFR   */
#define OCF2  7
#define TOV2  6
#define ICF1  5
#define OCF1A 4
#define OCF1B 3
#define TOV1  2
#define OCF0  1
#define TOV0  0

/*  SFIOR   */
#define ADTS2 7
#define ADTS1 6
#define ADTS0 5
#define ACME  3
#define PUD   2
#define PSR2  1
#define PSR10 0

typedef void (*pf)(void);

void TIM0_voidInit(void);

void TIM0_voidEnableOVInterrupt(void);
void TIM0_voidDisableOVInterrupt(void);
void TIM0_voidSetOVReg(u8 u8OVRegValue);
u8 TIM0_u8ReadOVReg(void);
void TIM0_voidOVSetCallBack(pf OVFunctionAddress);

void TIM0_voidEnableCTCInterrupt(void);
void TIM0_voidDisableCTCInterrupt(void);
void TIM0_voidSetCTCReg(u8 u8CTCRegValue);
u8 TIM0_u8ReadCTCReg(void);
void TIM0_voidCTCSetCallBack(pf CTCFunctionAddress);

void TIM0_voidSetDutyCycle(u8 u8DutyCycle);

#endif
