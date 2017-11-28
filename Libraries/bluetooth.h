#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"

#define USART_RX_BUFFER_SIZE 20

const uint16_t BT_TX = GPIO_Pin_2;
const uint16_t BT_RX = GPIO_Pin_3;
GPIO_TypeDef* BT_GPIO = GPIOA;
char BT_RX_Buffer[USART_RX_BUFFER_SIZE];
uint16_t BT_RX_Counter = 0;

void BT_RCC_init(void);
void BT_init(void);
void BT_IRQHandler(void);
//void USART2_IRQHandler() {
//	BT_IRQHandler();
//}

void BT_Run(void);

#endif
