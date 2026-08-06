#ifndef TIM0_PRIVATE_H
#define TIM0_PRIVATE_H

#define TCCR0   *((volatile u8*)0x53)
#define TCNT0   *((volatile u8*)0x52)
#define OCR0    *((volatile u8*)0x5C)
#define TIMSK   *((volatile u8*)0x59)
#define TIFR    *((volatile u8*)0x58)
#define DDRB    *((volatile u8*)0x37)

#endif
