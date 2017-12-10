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

void init_Timer2(void);
void TIM2_IRQHandler(void);

#endif /* TIMER_H_ */
