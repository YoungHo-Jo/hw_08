/*
 * touchSensor.c
 *
 *  Created on: 2017. 11. 27.
 *      Author: hw_8
 */

#ifndef __TOUCH_SENSOR_H__
#define __TOUCH_SENSOR_H__

#include "misc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"


void EXTI1_IRQHandler(void);
void EXTI9_5_IRQHandler(void);

void GPIO_Touch_Init(GPIO_TypeDef * GPIO_x,
		             uint16_t GPIO_Pin_x,
		             uint8_t GPIO_PortSource_x,
		             uint8_t GPIO_PinSource_x,
		             uint32_t EXTI_Line_x,
		             uint8_t EXTI_x_IRQn);
void GPIO_Touch_Init_All(void);


#endif

