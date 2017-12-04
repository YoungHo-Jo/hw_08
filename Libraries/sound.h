#ifndef __SOUND_H__
#define __SOUND_H__

#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_rcc.h"
#include "init.h"

typedef struct {
	uint16_t SCL;
	uint16_t SDA;
} Sound_struct;


Sound_struct* Sound_Struct_init(void);

void Sound_RCC_init(void);
void Sound_init(void);
void Sound_Run(void);

void I2C2_Start(void);
void I2C2_Send_Byte(uint8_t b);
uint8_t I2C2_wait_ACK(void);
void I2C2_Stop(void);





#endif

