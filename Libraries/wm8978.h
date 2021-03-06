#ifndef __WM8978_H__
#define __WM8978_H__

#include "init.h"
#include "sound.h"
////////////////////////////////////////////////// ////////////////////////////////
// This program is for educational use only and may not be used for any other purpose without the permission of the author
// ALIENTEK STM32F407 development board
// WM8978 driver code
// punctual atom @ ALIENTEK
// Technical Forum: www.openedv.com
// Created on: 2014/5/24
// Version: V1.0
// Copyright, piracy must study.
// Copyright (C) Guangzhou Star Electronic Technology Co., Ltd. 2014-2024
// All rights reserved
////////////////////////////////////////////////// ////////////////////////////////

#define WM8978_ADDR 0X1A // WM8978 device address, fixed as 0X1A 0011010

#define EQ1_80Hz 0X00
#define EQ1_105Hz 0X01
#define EQ1_135Hz 0X02
#define EQ1_175Hz 0X03

#define EQ2_230Hz 0X00
#define EQ2_300Hz 0X01
#define EQ2_385Hz 0X02
#define EQ2_500Hz 0X03

#define EQ3_650Hz 0X00
#define EQ3_850Hz 0X01
#define EQ3_1100Hz 0X02
#define EQ3_14000Hz 0X03

#define EQ4_1800Hz 0X00
#define EQ4_2400Hz 0X01
#define EQ4_3200Hz 0X02
#define EQ4_4100Hz 0X03

#define EQ5_5300Hz 0X00
#define EQ5_6900Hz 0X01
#define EQ5_9000Hz 0X02
#define EQ5_11700Hz 0X03

uint8_t WM8978_Init (void);
void WM8978_ADDA_Cfg (uint8_t dacen, uint8_t adcen);
void WM8978_Input_Cfg (uint8_t micen, uint8_t lineinen, uint8_t auxen);
void WM8978_Output_Cfg (uint8_t dacen, uint8_t bpsen);
void WM8978_MIC_Gain (uint8_t gain);
void WM8978_LINEIN_Gain (uint8_t gain);
void WM8978_AUX_Gain (uint8_t gain);
uint8_t WM8978_Write_Reg (uint8_t reg, uint16_t val);
uint16_t WM8978_Read_Reg (uint8_t reg);
void WM8978_HPvol_Set (uint8_t voll, uint8_t volr);
void WM8978_SPKvol_Set (uint8_t volx);
void WM8978_I2S_Cfg (uint8_t fmt, uint8_t len);
void WM8978_3D_Set (uint8_t depth);
void WM8978_EQ_3D_Dir (uint8_t dir);
void WM8978_EQ1_Set (uint8_t cfreq, uint8_t gain);
void WM8978_EQ2_Set (uint8_t cfreq, uint8_t gain);
void WM8978_EQ3_Set (uint8_t cfreq, uint8_t gain);
void WM8978_EQ4_Set (uint8_t cfreq, uint8_t gain);
void WM8978_EQ5_Set (uint8_t cfreq, uint8_t gain);

#endif
