#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_dma.h"
#include "init.h"

#define TERMINAL_RX_BUFFER_SIZE (1000)

typedef struct {
	uint16_t TX;
	uint16_t RX;
	GPIO_TypeDef* GPIO;
	char RX_Buffer[TERMINAL_RX_BUFFER_SIZE];
	uint16_t RX_Counter;
	uint8_t readyToSend;
} T_Struct;

// reserved function in CORTEXT-M3
void USART1_IRQHandler(void);

T_Struct* T_Struct_Init(void);
void T_Init(void);
void T_IRQHandler(void);
void T_Run(void);
void T_SendToBT(void);
void T_StoreInBuf(uint16_t c);
void T_RCC_Init(void);

#endif



