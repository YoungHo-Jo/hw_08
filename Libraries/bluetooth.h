#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_dma.h"

#define BT_RX_BUFFER_SIZE (1000)

typedef struct {
	uint16_t TX;
	uint16_t RX;
	GPIO_TypeDef* GPIO;
	char RX_Buffer[BT_RX_BUFFER_SIZE];
	uint16_t RX_Counter;
} BT_Struct;


void BT_Struct_Init(void);
void BT_Rcc_Init(void);
void BT_Init(void);
void USART2_IRQHandler(void);

#endif



