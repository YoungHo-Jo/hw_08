#ifndef __PIEZO_H__
#define __PIEZO_H__

#include "stm32f10x.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"

void PIEZO_RCC_init(void);
void PIEZO_init(void);
void Delay(__IO uint32_t nCount);


#endif