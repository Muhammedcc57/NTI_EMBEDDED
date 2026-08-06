#ifndef KPD_INTERFACE_H
#define KPD_INTERFACE_H

#include "STD_Types.h"

#define KPD_NOT_PRESSED    0xFF

void KEYPAD_voidInit(void);
u8 KEYPAD_u8GetPressedKey(void);

#endif