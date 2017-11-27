/*
 * touchSensor.c
 *
 *  Created on: 2017. 11. 27.
 *      Author: hw_8
 */

#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "misc.h"

const uint16_t TOUCH_A = GPIO_Pin_0;
const uint16_t TOUCH_B = GPIO_Pin_1;
const uint16_t TOUCH_C = GPIO_Pin_2;
const uint16_t TOUCH_D = GPIO_Pin_3;
const uint16_t TOUCH_E = GPIO_Pin_4;
const uint16_t TOUCH_F = GPIO_Pin_5;
const uint16_t TOUCH_G = GPIO_Pin_6;


/**
 * Returns GPIO_PinSource according to the paramter GPIO_Pin
 */
int syllable = 0;

typedef struct __GPIO_setting_data {
    uint8_t pin_src;
    uint32_t exti_line;
    uint32_t exti_irqn;
    uint8_t port_src;
    GPIO_TypeDef * GPIOx;
} GPIO_setting_data;

GPIO_setting_data get_GPIO_Setting_Data(uint16_t key) {
    GPIO_setting_data gpio_setting_data;

    switch(key) {
        case (TOUCH_A) :
            	gpio_setting_data.pin_src = GPIO_PinSource0;
				gpio_setting_data.exti_line = EXTI_Line0;
				gpio_setting_data.exti_irqn = EXTI0_IRQn;
				gpio_setting_data.port_src = GPIO_PortSourceGPIOA;
				gpio_setting_data.GPIOx = GPIOA;
            	break;
        case (TOUCH_B) :
				gpio_setting_data.pin_src = GPIO_PinSource0;
				gpio_setting_data.exti_line = EXTI_Line0;
				gpio_setting_data.exti_irqn = EXTI0_IRQn;
				gpio_setting_data.port_src = GPIO_PortSourceGPIOA;
				gpio_setting_data.GPIOx = GPIOA;
		        break;
        case (TOUCH_C) :
				gpio_setting_data.pin_src = GPIO_PinSource0;
				gpio_setting_data.exti_line = EXTI_Line0;
				gpio_setting_data.exti_irqn = EXTI0_IRQn;
				gpio_setting_data.port_src = GPIO_PortSourceGPIOA;
				gpio_setting_data.GPIOx = GPIOA;
		           break;
        case (TOUCH_D) :
				gpio_setting_data.pin_src = GPIO_PinSource0;
				gpio_setting_data.exti_line = EXTI_Line0;
				gpio_setting_data.exti_irqn = EXTI0_IRQn;
				gpio_setting_data.port_src = GPIO_PortSourceGPIOA;
				gpio_setting_data.GPIOx = GPIOA;
		        break;
        case TOUCH_E:
        		gpio_setting_data.pin_src = GPIO_PinSource0;
        		gpio_setting_data.exti_line = EXTI_Line0;
        		gpio_setting_data.exti_irqn = EXTI0_IRQn;
        		gpio_setting_data.port_src = GPIO_PortSourceGPIOA;
        		gpio_setting_data.GPIOx = GPIOA;
        	    break;
        case TOUCH_F:
        		gpio_setting_data.pin_src = GPIO_PinSource0;
        		gpio_setting_data.exti_line = EXTI_Line0;
        		gpio_setting_data.exti_irqn = EXTI0_IRQn;
        		gpio_setting_data.port_src = GPIO_PortSourceGPIOA;
        		gpio_setting_data.GPIOx = GPIOA;
        	    break;
        case TOUCH_G:
        		gpio_setting_data.pin_src = GPIO_PinSource0;
        		gpio_setting_data.exti_line = EXTI_Line0;
        		gpio_setting_data.exti_irqn = EXTI0_IRQn;
        		gpio_setting_data.port_src = GPIO_PortSourceGPIOA;
        		gpio_setting_data.GPIOx = GPIOA;
        	    break;
    }
    return gpio_setting_data;
}


void GPIO_touch_init(uint16_t key) {
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
    	GPIO_setting_data gpio_setting_data = get_GPIO_Setting_Data(key);

	GPIO_InitStructure.GPIO_Pin = key; // do
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(gpio_setting_data.GPIOx, &GPIO_InitStructure);
	GPIO_EXTILineConfig(gpio_setting_data.port_src, gpio_setting_data.pin_src);

	EXTI_InitStructure.EXTI_Line = gpio_setting_data.exti_line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = gpio_setting_data.exti_irqn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
