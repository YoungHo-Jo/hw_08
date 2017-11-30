
#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__
#define USART_RX_BUFFER_SIZE 20

#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"

typedef struct {
	uint16_t BT_TX;
	uint16_t BT_RX;
	GPIO_TypeDef* BT_GPIO;
	char BT_RX_Buffer[USART_RX_BUFFER_SIZE];
	uint16_t BT_RX_Counter;
} BT_Struct;

void BT_Struct_Init(void);
void BT_RCC_init(void);
void BT_init(void);
void BT_IRQHandler(void);
void USART2_IRQHandler(void);

void BT_Run(void);

#endif