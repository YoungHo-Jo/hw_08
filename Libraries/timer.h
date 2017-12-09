/*
 * timer.h
 *
 *  Created on: 2017. 12. 7.
 *      Author: hw_4
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "lcd.h"
#include "misc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"

#define RECORD_LEN 20000

void Init_Sound_Timer2(void);
void TIM2_IRQHandler(void);
void GPIO_Button_Init(void);
void EXTI15_10_IRQHandler(void);

#endif /* TIMER_H_ */
