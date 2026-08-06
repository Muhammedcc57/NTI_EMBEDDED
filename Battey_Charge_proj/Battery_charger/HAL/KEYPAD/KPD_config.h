#ifndef KPD_CONFIG_H
#define KPD_CONFIG_H

/* Rows */

#define KPD_R0    PORTC,PIN0
#define KPD_R1    PORTC,PIN1
#define KPD_R2    PORTC,PIN2
#define KPD_R3    PORTC,PIN3

/* Columns */

#define KPD_C0    PORTC,PIN4
#define KPD_C1    PORTC,PIN5
#define KPD_C2    PORTC,PIN6
#define KPD_C3    PORTC,PIN7

/* Keypad Size */

#define KPD_ROWS_NUM    4
#define KPD_COLS_NUM    4

/* Keys */

#define KPD_KEYS           \
{                          \
{'7','8','9','/'},         \
{'4','5','6','*'},         \
{'1','2','3','-'},         \
{'C','0','=','+'}          \
}

#endif