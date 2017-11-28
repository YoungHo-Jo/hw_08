#include "pressureSensor.h"

/**
 * Returns GPIO_PinSource according to the paramter GPIO_Pin
 */
uint8_t getPressurePinSrc(uint16_t pressureGPIO) {
    switch(pressureGPIO) {
        case PRESSURE_a:
            return GPIO_PinSource0;
        case PRESSURE_b:
            return GPIO_PinSource0;
        case PRESSURE_c:
            return GPIO_PinSource0;
        case PRESSURE_d:
            return GPIO_PinSource0;
        case PRESSURE_e:
            return GPIO_PinSource0;
        case PRESSURE_f:
            return GPIO_PinSource0;
        case PRESSURE_g:
            return GPIO_PinSource0;
    }
}


/**
 * Returns EXTI_Line according to the paramter GPIO_Pin
 */
uint32_t get_pressure_EXTI_Line(uint16_t pressureGPIO) {
    switch(pressureGPIO) {
        case PRESSURE_a:
            return EXTI_Line0;
        case PRESSURE_b:
            return EXTI_Line0;
        case PRESSURE_c:
            return EXTI_Line0;
        case PRESSURE_d:
            return EXTI_Line0;
        case PRESSURE_e:
            return EXTI_Line0;
        case PRESSURE_f:
            return EXTI_Line0;
        case PRESSURE_g:
            return EXTI_Line0;
    }
}

/**
 * Returns EXTI_IRQn according to the paramter GPIO_Pin
 */
uint32_t get_pressure_EXIT_IRQn(uint16_t pressureGPIO) {
    switch(pressureGPIO) {
        case PRESSURE_a:
            return EXTI0_IRQn;
        case PRESSURE_b:
            return EXTI0_IRQn;
        case PRESSURE_c:
            return EXTI0_IRQn;
        case PRESSURE_d:
            return EXTI0_IRQn;
        case PRESSURE_e:
            return EXTI0_IRQn;
        case PRESSURE_f:
            return EXTI0_IRQn;
        case PRESSURE_g:
            return EXTI0_IRQn;
    }
}

/**
 * Returns GPIO_PinSource according to the parameter GPIO_pin
 *
 */
uint8_t get_pressure_GPIO_PinSource(uint16_t pressureGPIO) {
    switch(pressureGPIO) {
        case PRESSURE_a:
            return GPIO_PortSourceGPIOA;
        case PRESSURE_b:
            return GPIO_PortSourceGPIOA;
        case PRESSURE_c:
            return GPIO_PortSourceGPIOA;
        case PRESSURE_d:
            return GPIO_PortSourceGPIOA;
        case PRESSURE_e:
            return GPIO_PortSourceGPIOA;
        case PRESSURE_f:
            return GPIO_PortSourceGPIOA;
        case PRESSURE_g:
            return GPIO_PortSourceGPIOA;
    }
}

/**
 * Returns GPIO_typeDef according to the parameter GPIO_Pin
 *
 */
 GPIO_TypeDef* get_pressure_GPIO_TypeDef(uint16_t pressureGPIO) {
    switch(pressureGPIO) {
        case PRESSURE_a:
            return GPIOA;
        case PRESSURE_b:
            return GPIOA;
        case PRESSURE_c:
            return GPIOA;
        case PRESSURE_d:
            return GPIOA;
        case PRESSURE_e:
            return GPIOA;
        case PRESSURE_f:
            return GPIOA;
        case PRESSURE_g:
            return GPIOA;
    }
 }

/**
 * Sets GPIO Sensor
 *
 *
 */
void GPIO_pressure_init(GPIO_TypeDef* GPIOx, uint16_t pin) {
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	GPIO_InitStructure.GPIO_Pin = pin; // do
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(get_pressure_GPIO_TypeDef(pin), &GPIO_InitStructure);
	GPIO_EXTILineConfig(get_pressure_GPIO_PinSource(pin), getPressurePinSrc(pin));

	EXTI_InitStructure.EXTI_Line = get_pressure_EXTI_Line(pin);
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = get_pressure_EXIT_IRQn(pin);
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}



