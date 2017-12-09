/*
 * piezo.h
 *
 *  Created on: 2017. 12. 9.
 *      Author: hw_5
 */

#ifndef PIEZO_H_
#define PIEZO_H_

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x.h"
#include "misc.h"

void Piezo_Config(void);
void setSound(uint32_t syll);

#endif /* PIEZO_H_ */
