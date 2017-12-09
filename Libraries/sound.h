#ifndef __SOUND_H__
#define __SOUND_H__

#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_dma.h"
#include "init.h"
#include "wm8978.h"


#define I2C2_MASTER_ADDR 0x00

typedef struct {
	uint16_t SCL;
	uint16_t SDA;
	GPIO_TypeDef* GPIO;
} Sound_struct;


Sound_struct* Sound_Struct_Init(void);

void Sound_RCC_Init(void);
void Sound_Init(void);
void Sound_Run(void);

//// test function
void Sound_Test_Init(void);
void Sound_Test_Run(void);
////

void I2C2_StartTransmission(uint8_t transmissionDirection, uint8_t slaveAddress);
void I2C2_WriteData(uint8_t data);
uint8_t I2C2_ReadData(void);
void I2C2_Stop(void);

void I2S2_TX_DMA_Init(u8*, u8*, u16);

static u8 buf[100] = {
		0x22, 0x22, 0x12, 0x78, 0x02,
		0x32, 0x22, 0x22, 0x52, 0x02,
		0x42, 0x22, 0x32, 0x23, 0x02,
		0x52, 0x22, 0x52, 0x40, 0x02,
		0x62, 0x22, 0xf2, 0x59, 0x02,
		0x72, 0x22, 0xe2, 0x12, 0x02,
		0x82, 0x22, 0xd2, 0x01, 0x02,
};

#endif

