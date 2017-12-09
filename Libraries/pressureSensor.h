#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "misc.h"


void GPIO_config(void);
void adc_config(void);

#endif
