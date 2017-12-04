#include "wm8978.h"
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

// WM8978 register value buffer (a total of 58 registers, 0 ~ 57), occupying 116 bytes of memory
// Because the IIC operation of WM8978 does not support read operations, all register values �뗢�땇re saved locally
// When writing WM8978 register, it synchronously updates to the local register value. When reading the register, it directly returns the register value saved locally.
// Note: The register value of WM8978 is 9 bits, so use uint16_t to store.
static uint16_t WM8978_REGVAL_TBL[58] = { 0X0000, 0X0000, 0X0000, 0X0000,
		0X0050, 0X0000, 0X0140, 0X0000, 0X0000, 0X0000, 0X0000, 0X00FF, 0X00FF,
		0X0000, 0X0100, 0X00FF, 0X00FF, 0X0000, 0X012C, 0X002C, 0X002C, 0X002C,
		0X002C, 0X0000, 0X0032, 0X0000, 0X0000, 0X0000, 0X0000, 0X0000, 0X0000,
		0X0000, 0X0038, 0X000B, 0X0032, 0X0000, 0X0008, 0X000C, 0X0093, 0X00E9,
		0X0000, 0X0000, 0X0000, 0X0000, 0X0003, 0X0010, 0X0010, 0X0100, 0X0100,
		0X0002, 0X0001, 0X0001, 0X0039, 0X0039, 0X0039, 0X0039, 0X0001, 0X0001 };
// WM8978 initialization
// Return value: 0, initialization is normal
// other, error code
uint8_t WM8978_Init(void) {
	uint8_t res;

	res = WM8978_Write_Reg(0, 0); // soft reset WM8978
	if (res)
		return 1;
	// instruction failed to send, WM8978 exception
	// The following is a general setting
	// set MICEN to 1 (MIC enabled), BIASEN set to 1 (simulator work), VMIDSEL [1: 0] set to: 11 (5K) WM8978_Write_Reg (1,0X1B)
	WM8978_Write_Reg (2,0X1B0);// R2, ROUT1, LOUT1 output enable (headphone can work), BOOSTENR, BOOSTENL enable
	WM8978_Write_Reg(3, 0X6C); // R3, LOUT2, ROUT2 output enable (speaker work), RMIX, LMIX enable
	WM8978_Write_Reg(6, 0); // R6, MCLK is provided externally
	WM8978_Write_Reg(43, 1 << 4); // R43, INVROUT2 reverse, drive horn
	WM8978_Write_Reg(47, 1 << 8); // R47 setting, PGABOOSTL, gain 20 times gain for left channel MIC
	WM8978_Write_Reg(48, 1 << 8); // R48 set, PGABOOSTR, right channel MIC gain 20 times gain
	WM8978_Write_Reg(49, 1 << 1); // R49, TSDEN, open overheat protection
	WM8978_Write_Reg(10, 1 << 3); // R10, SOFTMUTE off, 128x sample, best SNR
	WM8978_Write_Reg(14, 1 << 3); // R14, ADC 128x sample rate

	//// playback settings
	// WM8978_ADDA_Cfg (1,0); // Turn on the DAC
	// WM8978_Input_Cfg (0,0,0); // close the input channel
	// WM8978_Output_Cfg (1,0); // Turn on the DAC output
	//// recording settings
	// WM8978_ADDA_Cfg (0,1); // turn on the ADC
	// WM8978_Input_Cfg (1,1,0); // Turn on the MIC & LINE IN
	// WM8978_Output_Cfg (1,0); // turn on BYPASS output
	// WM8978_MIC_Gain (46); // MIC gain setting
	// WM8978_HPvol_Set (25,25);
	// WM8978_SPKvol_Set (30); // 50


	// Simultaneous recording and playback settings
	WM8978_ADDA_Cfg(1, 1); // Turn on the DAC
	WM8978_Input_Cfg(1, 1, 0); // Turn on the MIC & LINE IN
	WM8978_Output_Cfg(1, 0); // Turn on the DAC output
	WM8978_MIC_Gain(46); // MIC gain setting
	WM8978_HPvol_Set(25, 25);
	WM8978_SPKvol_Set(30); // 50
	return 0;
}

// WM8978 write register
// reg: register address
// val: The value to be written to the register
// return value: 0, success;
// other, error code
uint8_t WM8978_Write_Reg(uint8_t reg, uint16_t val) {
// HAL_StatusTypeDef res;
// uint8_t val_L = val & 0xff;
// res = HAL_I2C_Mem_Write (& hi2c1, WM8978_ADDR << 1, (reg << 1) | ((val >> 8) & 0x01), 1, & val_L, 1, HAL_MAX_DELAY);
//
// if (res! = HAL_OK)
// {
// printf ("% s,% d, res =% d! \ n", __ FUNCTION __, __ LINE __, res);
//}

	/*
	IIC_Start();
	IIC_Send_Byte((WM8978_ADDR << 1) | 0); // Send Device Address + Write Command
	if (IIC_Wait_Ack ())
	혻혻혻혻혻혻혻혻printf ("% s,% d \ n", __ FUNCTION __, 1); // wait for reply (successful? / failed?)
	혻혻혻혻IIC_Send_Byte((reg << 1) | ((val >> 8) & 0X01)); // write register address + the most significant bit of data
	if (IIC_Wait_Ack ())
	혻혻혻혻혻혻혻혻printf ("% s,% d \ n", __ FUNCTION __, 2); // wait for reply (successful? / failed?)
	IIC_Send_Byte(val & 0xFF); // Send data
	if (IIC_Wait_Ack ())
	혻혻혻혻혻혻혻혻printf ("% s,% d \ n", __FUNCTION __, 3); // wait for reply (successful? / failed?)
	혻혻혻혻IIC_Stop();
	*/

	I2C2_StartTransmission(I2C_Direction_Transmitter, WM8978_ADDR);
	I2C2_WriteData((reg<<1) | ((val>>8) & 0x01));
	I2C2_Stop();
	WM8978_REGVAL_TBL[reg] = val; // Save the register value locally
	return 0;
}


// WM8978 read register
// is to read the corresponding value in the local register buffer
// reg: register address
// Return value: register value
uint16_t WM8978_Read_Reg(uint8_t reg) {
	return WM8978_REGVAL_TBL[reg];
}


// WM8978 DAC / ADC configuration
// adcen: adc enable (1) / off (0)
// dacen: dac enable (1) / off (0)
void WM8978_ADDA_Cfg(uint8_t dacen, uint8_t adcen) {
	uint16_t regval;
	regval = WM8978_Read_Reg(3); // read R3
	if (dacen) {
		regval |= 3 << 0; // The lowest 2 bits of R3 are set as 1 to enable DACR & DACL
	} else {
		regval &= ~(3 << 0);// The least significant 2 bits of R3 are cleared to 0, turning DACR & DACL off.
	}

	WM8978_Write_Reg(3, regval); // Set R3
	regval = WM8978_Read_Reg(2); // read R2
	if (adcen) {
		regval |= 3 << 0; // The lowest 2 bits of R2 are set to 1, turning on ADCR & ADCL
	} else {
		regval &= ~(3 << 0);// The lowest 2 bits of R2 are cleared to 0 to disable ADCR & ADCL.
	}
	WM8978_Write_Reg(2, regval); // Set R2
}

// WM8978 input channel configuration
// micen: MIC on (1) / off (0)
// lineinen: Line In on (1) / off (0)
// auxen: aux on (1) / off (0)
void WM8978_Input_Cfg(uint8_t micen, uint8_t lineinen, uint8_t auxen) {
	uint16_t regval;
	regval = WM8978_Read_Reg(2); // read R2
	if (micen) {
		regval |= 3 << 2; // open INPPGAENR, INPPGAENL (MIC PGA amplification)
	}

	else {
		regval &= ~(3 << 2);// Close INPPGAENR, INPPGAENL.
	}

	WM8978_Write_Reg(2, regval); // Set R2

	regval = WM8978_Read_Reg(44); // read R44
	if (micen) {
		regval |= 3 << 4 | 3 << 0; // Turn on LIN2INPPGA, LIP2INPGA, RIN2INPPGA, RIP2INPGA.
	} else {
		regval &= ~ (3 << 4 | 3 << 0);// Close LIN2INPPGA, LIP2INPGA, RIN2INPPGA, RIP2INPGA.
	}
	WM8978_Write_Reg(44, regval); // Set R44

	if (lineinen) {
		WM8978_LINEIN_Gain(5); // LINE IN 0dB gain
	} else {
		WM8978_LINEIN_Gain(0); // Close LINE IN
	}
	if (auxen) {
		WM8978_AUX_Gain(7); // AUX 6dB gain
	} else {
		WM8978_AUX_Gain(0); // Turn off the AUX input
	}
}

// WM8978 output configuration
// dacen: DAC output (playback) on (1) / off (0)
// bpsen: Bypass output (recording including MIC, LINE IN, AUX etc.) On (1) / Off (0)
void WM8978_Output_Cfg(uint8_t dacen, uint8_t bpsen) {
	uint16_t regval = 0;
	if (dacen) {
		regval |= 1 << 0; // DAC output is enabled
	}
	if (bpsen) {
		regval |= 1 << 1; // BYPASS enabled
		regval |= 5 << 2;// 0dB gain
	}
	WM8978_Write_Reg(50, regval); // R50 setting
	WM8978_Write_Reg(51, regval); // R51 settings
}
// WM8978 MIC Gain Settings (Excluding BOOST 20dB, MIC -> ADC Input Gain)
// gain: 0 ~ 63, corresponding to -12dB ~ 35.25dB, 0.75dB / Step
void WM8978_MIC_Gain(uint8_t gain) {
	gain &= 0X3F;
	WM8978_Write_Reg(45, gain); // R45, left channel PGA setting
	WM8978_Write_Reg(46, gain | 1 << 8); // R46, right channel PGA setting
}
// WM8978 L2 / R2 (ie Line In) gain setting (L2 / R2 -> gain of the ADC input section)
// gain: 0 ~ 7,0 means channel is disabled, 1 ~ 7, corresponding to -12dB ~ 6dB, 3dB / Step
void WM8978_LINEIN_Gain(uint8_t gain) {
	uint16_t regval;
	gain &= 0X07;
	regval = WM8978_Read_Reg(47); // read R47
	regval &= ~(7 << 4); // clear the original settings
	WM8978_Write_Reg(47, regval | gain << 4); // Set R47
	regval = WM8978_Read_Reg(48); // read R48
	regval &= ~(7 << 4); // clear the original settings
	WM8978_Write_Reg(48, regval | gain << 4); // Set R48
}


// WM8978 AUXR, AUXL (PWM Audio Section) Gain Settings (AUXR / L -> ADC Input Section Gain)
// gain: 0 ~ 7,0 means channel is disabled, 1 ~ 7, corresponding to -12dB ~ 6dB, 3dB / Step
void WM8978_AUX_Gain(uint8_t gain) {
	uint16_t regval;
	gain &= 0X07;
	regval = WM8978_Read_Reg(47); // read R47
	regval &= ~(7 << 0); // clear the original settings
	WM8978_Write_Reg(47, regval | gain << 0); // Set R47
	regval = WM8978_Read_Reg(48); // read R48
	regval &= ~(7 << 0); // clear the original settings
	WM8978_Write_Reg(48, regval | gain << 0); // Set R48
}


// Set I2S working mode
// fmt: 0, LSB (right justified); 1, MSB (left justified); 2, Philips I2S standard;
// len: 0,16 bits; 1,20 bits; 2,24 bits; 3,32 bits;
void WM8978_I2S_Cfg(uint8_t fmt, uint8_t len) {
	fmt &= 0X03;
	len &= 0X03; // limited range
	WM8978_Write_Reg(4, (fmt << 3) | (len << 5)); // R4, WM8978 working mode settings
}

// Set the left and right channel volume of the earphone
// voll: left channel volume (0 ~ 63)
// volr: right channel volume (0 ~ 63)
void WM8978_HPvol_Set(uint8_t voll, uint8_t volr) {
	voll &= 0X3F;
	volr &= 0X3F; // limited range
	if (voll == 0) {
		voll |= 1 << 6; // volume is 0, the direct mute
	}
	if (volr == 0) {
		volr |= 1 << 6; // volume is 0, the direct mute
	}
	WM8978_Write_Reg(52, voll);// R52, headphone left channel volume settings
	WM8978_Write_Reg(53, volr | (1<<8)); // (R53, right channel volume setting of the earphone, synchronization update (HPVU = 1)
}

// Set the speaker volume
// voll: left channel volume (0 ~ 63)
void WM8978_SPKvol_Set(uint8_t volx) {
	volx &= 0X3F; // limited range
	if (volx == 0) {
		volx |= 1 << 6; // When the volume is 0, direct mute
	}
	WM8978_Write_Reg(54, volx); // R54, speaker left channel volume setting
	WM8978_Write_Reg (55, volx | (1<<8)); // (R55, right speaker volume setting, sync update (SPKVU = 1)
}

// Set 3D surround sound
// depth: 0 ~ 15 (3D strength, 0 weakest, 15 strongest)
void WM8978_3D_Set(uint8_t depth) {
	depth &= 0XF; // limited range
	WM8978_Write_Reg(41, depth); // R41, 3D surround settings
}

// Set the direction of EQ / 3D action
// dir: 0, works on the ADC
// 1, works on DAC (default)
void WM8978_EQ_3D_Dir(uint8_t dir) {
	uint16_t regval;
	regval = WM8978_Read_Reg(0X12);
	if (dir) {
		regval |= 1 << 8;
	} else {
		regval &= ~(1 << 8);
	}
	WM8978_Write_Reg(18, regval); // R18, EQ1, the ninth control EQ / 3D direction
}

// Set EQ1
// cfreq: cut-off frequency, 0 ~ 3, corresponding to: 80/105/135 / 175Hz
// gain: Gain, 0 ~ 24, corresponding to -12 ~ + 12dB
void WM8978_EQ1_Set(uint8_t cfreq, uint8_t gain) {
	uint16_t regval;
	cfreq &= 0X3; // limited range
	if (gain > 24) {
		gain = 24;
	}
	gain = 24 - gain;
	regval = WM8978_Read_Reg(18);
	regval &= 0X100;
	regval |= cfreq << 5; // Set the cut-off frequency
	regval |= gain;// Set the gain
	WM8978_Write_Reg(18, regval); // R18, EQ1 settings
}

// Set EQ2
// cfreq: center frequency, 0 ~ 3, corresponding to: 230/300/385 / 500Hz
// gain: Gain, 0 ~ 24, corresponding to -12 ~ + 12dB
void WM8978_EQ2_Set(uint8_t cfreq, uint8_t gain) {
	uint16_t regval = 0;
	cfreq &= 0X3; // limited range
	if (gain > 24) {
		gain = 24;
	}
	gain = 24 - gain;
	regval |= cfreq << 5; // Set the cut-off frequency
	regval |= gain;// Set the gain
	WM8978_Write_Reg(19, regval); // R19, EQ2 settings
}


// Set EQ3
// cfreq: Center frequency, 0 ~ 3, corresponding to: 650/850/1100 / 1400Hz
// gain: Gain, 0 ~ 24, corresponding to -12 ~ + 12dB
void WM8978_EQ3_Set(uint8_t cfreq, uint8_t gain) {
	uint16_t regval = 0;
	cfreq &= 0X3; // limited range
	if (gain > 24) {
		gain = 24;
	}
	gain = 24 - gain;
	regval |= cfreq << 5; // Set the cut-off frequency
	regval |= gain;// Set the gain
	WM8978_Write_Reg(20, regval); // R20, EQ3 settings
}

// Set EQ4
// cfreq: Center frequency, 0 ~ 3, corresponding to: 1800/2400/3200 / 4100Hz
// gain: Gain, 0 ~ 24, corresponding to -12 ~ + 12dB
void WM8978_EQ4_Set(uint8_t cfreq, uint8_t gain) {
	uint16_t regval = 0;
	cfreq &= 0X3; // limited range
	if (gain > 24) {
		gain = 24;
	}
	gain = 24 - gain;
	regval |= cfreq << 5; // Set the cut-off frequency
	regval |= gain;// Set the gain
	WM8978_Write_Reg(21, regval); // R21, EQ4 settings
}


// Set EQ5
// cfreq: center frequency, 0 ~ 3, corresponding to: 5300/6900/9000 / 11700Hz
// gain: Gain, 0 ~ 24, corresponding to -12 ~ + 12dB
void WM8978_EQ5_Set(uint8_t cfreq, uint8_t gain) {
	uint16_t regval = 0;
	cfreq &= 0X3; // limited range
	if (gain > 24) {
		gain = 24;
	}
	gain = 24 - gain;
	regval |= cfreq << 5; // Set the cut-off frequency
	regval |= gain;// Set the gain
	WM8978_Write_Reg(22, regval); // R22, EQ5 settings
}
