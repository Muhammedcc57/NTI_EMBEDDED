/*
 * main.c
 *
 *  Created on: Aug 1, 2026
 *      Author: Mohammed Omera
 */
#include "../LIB/STD_TYPES.h"
#include "../HAL/LCD/CLCD_interface.h"
#include <avr/io.h>
int main(void)
{
    CLCD_voidInit();

    CLCD_voidSendData('A');

    while(1)
    {

    }

    return 0;
}
