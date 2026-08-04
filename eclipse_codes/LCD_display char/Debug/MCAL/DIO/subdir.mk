################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/DIO/DIO_program.c 

OBJS += \
./MCAL/DIO/DIO_program.o 

C_DEPS += \
./MCAL/DIO/DIO_program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/DIO/%.o: ../MCAL/DIO/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\Mohammed Omera\Desktop\NTI_Simulation\first_code\HAL\LCD" -I"C:\Users\Mohammed Omera\Desktop\NTI_Simulation\first_code\MCAL\DIO" -I"C:\Users\Mohammed Omera\Desktop\NTI_Simulation\first_code\LIB" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


