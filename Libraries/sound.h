#ifndef __SOUND_H__
#define __SOUND_H__

#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_rcc.h"
#include "init.h"
#include "wm8978.h"

#define I2C2_MASTER_ADDR 0x00

typedef struct {
	uint16_t SCL;
	uint16_t SDA;
	GPIO_TypeDef* GPIO;
} Sound_struct;


Sound_struct* Sound_Struct_init(void);

void Sound_RCC_init(void);
void Sound_init(void);
void Sound_Run(void);

void I2C2_StartTransmission(uint8_t transmissionDirection, uint8_t slaveAddress);
void I2C2_WriteData(uint8_t data);
uint8_t I2C2_ReadData(void);
void I2C2_Stop(void);

#endif

