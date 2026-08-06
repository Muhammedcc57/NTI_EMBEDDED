################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/main.c 

OBJS += \
./APP/main.o 

C_DEPS += \
./APP/main.d 


# Each subdirectory must supply rules for building sources it contributes
APP/%.o: ../APP/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\NTI\Battery_charger\HAL\KEYPAD" -I"C:\NTI\Battery_charger\HAL\LCD" -I"C:\NTI\Battery_charger\LIB" -I"C:\NTI\Battery_charger\MCAL\ADC" -I"C:\NTI\Battery_charger\MCAL\DIO" -I"C:\NTI\Battery_charger\MCAL\EXTI" -I"C:\NTI\Battery_charger\MCAL\GIE" -I"C:\NTI\Battery_charger\MCAL\TIM0" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


