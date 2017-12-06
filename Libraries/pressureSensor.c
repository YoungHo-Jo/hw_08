#include "pressureSensor.h"

GPIO_InitTypeDef myGPIO;
ADC_InitTypeDef myADC;
DMA_InitTypeDef DMA_InitStructure;

uint32_t pressure[3] = {0, 0, 0};

void GPIO_config(void) {
	// initialize LED C8, 9
	myGPIO.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 ; //
	myGPIO.GPIO_Mode = GPIO_Mode_AIN; //set as analog input
	GPIO_Init(GPIOA, &myGPIO); //set to C1, C2

	myGPIO.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 ; //
	myGPIO.GPIO_Mode = GPIO_Mode_AIN; //set as analog input
	GPIO_Init(GPIOA, &myGPIO); //set to C1, C2
}

void adc_config(void) {
	// adc gpio_input setting
	GPIO_config();

	//clock setting
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //clock for ADC (max 14MHz, 72/6=12MHz)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //enable ADC clock

	// DMA1 channel1 configuration ----------------------------------------------

	//configure ADC1 parameters
	myADC.ADC_Mode = ADC_Mode_Independent;
	myADC.ADC_ScanConvMode = ENABLE;
	myADC.ADC_ContinuousConvMode = ENABLE;
	myADC.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	myADC.ADC_DataAlign = ADC_DataAlign_Right;
	myADC.ADC_NbrOfChannel = 3;
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5); //PC1 as Input
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 2, ADC_SampleTime_55Cycles5); //PC2 as Input
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 3, ADC_SampleTime_55Cycles5); //PC2 as Input

	ADC_Init(ADC1, &myADC);
	ADC_Cmd(ADC1, ENABLE);

	//Calibrate ADC *optional?
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1))
		;
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1))
		;

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);

	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) &ADC1->DR;
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32) pressure;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 3;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; // 32bit
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word; // 32bit
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	// Enable DMA1 Channel1

	ADC_DMACmd(ADC1, ENABLE);
	DMA_Cmd(DMA1_Channel1, ENABLE);
}
