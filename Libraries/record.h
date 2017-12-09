#ifndef RECORD_H
#define RECORD_H

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"
#include "timer.h"
#include "lcd.h"
#include "misc.h"


#define RECORD_LEN 20000

void Init_Record_Timer4(void);
void TIM4_IRQHandler(void);
void GPIO_Button_Init(void);
void EXTI15_10_IRQHandler(void);

#endif
