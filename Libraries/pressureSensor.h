#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_exti.h"
#include "misc.h"

const uint16_t PRESSURE_a = GPIO_Pin_0;
const uint16_t PRESSURE_b = GPIO_Pin_1;
const uint16_t PRESSURE_c = GPIO_Pin_2;
const uint16_t PRESSURE_d = GPIO_Pin_3;
const uint16_t PRESSURE_e = GPIO_Pin_4;
const uint16_t PRESSURE_f = GPIO_Pin_5;
const uint16_t PRESSURE_g = GPIO_Pin_6;
/**
 * Returns GPIO_PinSource according to the paramter GPIO_Pin
 */
uint8_t getPressurePinSrc(uint16_t pressureGPIO);

/**
 * Returns EXTI_Line according to the paramter GPIO_Pin
 */
uint32_t get_pressure_EXTI_Line(uint16_t pressureGPIO);

/**
 * Returns EXTI_IRQn according to the paramter GPIO_Pin
 */
uint32_t get_pressure_EXIT_IRQn(uint16_t pressureGPIO);

/**
 * Returns GPIO_PinSource according to the parameter GPIO_pin
 *
 */
uint8_t get_pressure_GPIO_PinSource(uint16_t pressureGPIO);

/**
 * Returns GPIO_typeDef according to the parameter GPIO_Pin
 *
 */
 GPIO_TypeDef* get_pressure_GPIO_TypeDef(uint16_t pressureGPIO);

/**
 * Sets GPIO Sensor
 *
 *
 */
void GPIO_pressure_init(GPIO_TypeDef* GPIOx, uint16_t pin);


