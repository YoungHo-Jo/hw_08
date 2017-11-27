################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/STM32F10x_StdPeriph_Driver_v3.5/lcd_lib/Touch.c \
../Libraries/STM32F10x_StdPeriph_Driver_v3.5/lcd_lib/lcd.c 

OBJS += \
./Libraries/STM32F10x_StdPeriph_Driver_v3.5/lcd_lib/Touch.o \
./Libraries/STM32F10x_StdPeriph_Driver_v3.5/lcd_lib/lcd.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/STM32F10x_StdPeriph_Driver_v3.5/lcd_lib/%.o: ../Libraries/STM32F10x_StdPeriph_Driver_v3.5/lcd_lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc -I"C:\Users\hw_8\Documents\DS-5 Workspace\hw_team08\Libraries\CMSIS\CoreSupport" -I"C:\Users\hw_8\Documents\DS-5 Workspace\hw_team08\Libraries" -I"C:\Users\hw_8\Documents\DS-5 Workspace\hw_team08\Libraries\CMSIS\DeviceSupport" -I"C:\Users\hw_8\Documents\DS-5 Workspace\hw_team08\Libraries\CMSIS\DeviceSupport\Startup" -I"C:\Users\hw_8\Documents\DS-5 Workspace\hw_team08\Libraries\STM32F10x_StdPeriph_Driver_v3.5\inc" -I"C:\Users\hw_8\Documents\DS-5 Workspace\hw_team08\Libraries\STM32F10x_StdPeriph_Driver_v3.5\lcd_lib" -I"C:\Users\hw_8\Documents\DS-5 Workspace\hw_team08\Libraries\STM32F10x_StdPeriph_Driver_v3.5\src" -O0 --cpu=cortex-m3 -g -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


