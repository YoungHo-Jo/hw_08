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
#include "lcd.h"

typedef struct __GPIO_setting_data {
    uint8_t pin_src;
    uint32_t exti_line;
    uint32_t exti_irqn;
    uint8_t port_src;
    GPIO_TypeDef * GPIOx;
} GPIO_setting_data;

void EXTI1_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);

GPIO_setting_data get_GPIO_Setting_Data(uint16_t key);
void GPIO_touch_init(uint16_t key);
void GPIO_touch_init_all(void);
void TIM2_IRQHandler(void);
void init_Timer2(void);

#endif




