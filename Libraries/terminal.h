#ifndef TERMINAL_H
#define TERMINAL_H

#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_dma.h"

#define TERMINAL_RX_BUFFER_SIZE (100) 

void Send_String_Usart2(int len);
void Terminal_Struct_init(); 
void Terminal_Rcc_init(); 
void Terminal_Init(); 
void USART1_IRQHandler(); 

#endif TERMINAL_H
