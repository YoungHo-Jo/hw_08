#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_dma.h"

#define BT_RX_BUFFER_SIZE (1000) 

void Send_String_Usart2(int len);
void BT_Struct_init(); 
void BT_Rcc_init(); 
void BT_Init(); 
void USART2_IRQHandler(); 

#endif 
