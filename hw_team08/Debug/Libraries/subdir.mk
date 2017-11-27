################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/bluetooth.c \
../Libraries/init.c \
../Libraries/lcdInit.c \
../Libraries/pressureSensor.c \
../Libraries/sound.c \
../Libraries/touchSensor.c 

OBJS += \
./Libraries/bluetooth.o \
./Libraries/init.o \
./Libraries/lcdInit.o \
./Libraries/pressureSensor.o \
./Libraries/sound.o \
./Libraries/touchSensor.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/%.o: ../Libraries/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc -I"C:\Users\hw_8\Documents\DS-5 Workspace\hw_team08\Libraries\CMSIS\CoreSupport" -I"C:\Users\hw_8\Documents\DS-5 Workspace\hw_team08\Libraries" -I"C:\Users\hw_8\Documents\DS-5 Workspace\hw_team08\Libraries\CMSIS\DeviceSupport" -I"C:\Users\hw_8\Documents\DS-5 Workspace\hw_team08\Libraries\CMSIS\DeviceSupport\Startup" -I"C:\Users\hw_8\Documents\DS-5 Workspace\hw_team08\Libraries\STM32F10x_StdPeriph_Driver_v3.5\inc" -I"C:\Users\hw_8\Documents\DS-5 Workspace\hw_team08\Libraries\STM32F10x_StdPeriph_Driver_v3.5\lcd_lib" -I"C:\Users\hw_8\Documents\DS-5 Workspace\hw_team08\Libraries\STM32F10x_StdPeriph_Driver_v3.5\src" -O0 --cpu=cortex-m3 -g -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


