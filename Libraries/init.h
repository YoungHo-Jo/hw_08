/*
 * init.h
 *
 *  Created on: 2017. 11. 27.
 *      Author: hw_8
 */
#ifndef __INIT_H__
#define __INIT_H__

#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#define TRUE 1
#define FALSE 0

void SysInit(void);
void SetSysClock(void);
void defaultSystemInit(void);


void initLED(void);
void setLED(uint8_t, uint8_t, uint8_t, uint8_t);

#endif
