#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include "init.h"
#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"

#define TERMINAL_RX_BUFFER_SIZE 1000

typedef struct {
	uint16_t TX;
	uint16_t RX;
	GPIO_TypeDef* GPIO;
	char RX_Buffer[TERMINAL_RX_BUFFER_SIZE];
	uint16_t RX_Counter;
	uint8_t readyToSend;
} Terminal_Struct;

// reserved function in CORTEXT-M3
void USART1_IRQHandler(void);

Terminal_Struct* Terminal_Struct_init(void);
void Terminal_Rcc_init(void);
void Terminal_init(void);
void Terminal_IRQHandler(void);
void Terminal_Run(void);

void Terminal_sendToBT(void);
void Terminal_storeInBuf(uint16_t c);

#endif
