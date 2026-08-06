#ifndef DIO_INT_H
#define DIO_INT_H


#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3



#define PIN0           0
#define PIN1           1
#define PIN2           2
#define PIN3           3
#define PIN4           4
#define PIN5           5
#define PIN6           6
#define PIN7           7



#define INPUT          0
#define OUTPUT         1



#define LOW            0
#define HIGH           1

void DIO_voidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction);
void DIO_voidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);
u8   DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin);
void DIO_voidSetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction);
void DIO_voidSetPortValue(u8 Copy_u8Port, u8 Copy_u8Value);

#endif
