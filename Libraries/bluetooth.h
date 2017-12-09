#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__
#define USART_RX_BUFFER_SIZE 1500

#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "init.h"
#include "timer.h"
#include "piezo.h"

typedef struct {
	uint16_t TX;
	uint16_t RX;
	GPIO_TypeDef* GPIO;
	char RX_Buffer[USART_RX_BUFFER_SIZE];
	uint16_t RX_Counter;
	uint8_t readyToSend;
} BT_Struct;


// reserved function
void USART2_IRQHandler(void);

BT_Struct* BT_Struct_Init(void);
void BT_RCC_Init(void);
void BT_Init(void);
void BT_IRQHandler(void);
void BT_Run(void);

void BT_SendToTerminal(void);
void BT_StoreInBuf(uint16_t c);

#endif



