#include "sound.h"


Sound_struct ss;

Sound_struct* Sound_Struct_init(void) {
	ss.SCL = GPIO_Pin_10;
	ss.SDA = GPIO_Pin_11;
	ss.GPIO = GPIOB;
	return &ss;
}

void Sound_RCC_init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2 | RCC_APB1Periph_SPI2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);


	// reset SPI2
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, ENABLE);
	// end reset SPI2
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, DISABLE);

	// i dont know it is really required.
	GPIO_AFIODeInit();
}

void Sound_init(void) {
	GPIO_InitTypeDef GPIOB_init_struct;

	// config I2C2 pins: SCL and SDA == GPIOB_Pin_10 and GPIOB_Pin_11
	// I2C needs Open Drain
	GPIOB_init_struct.GPIO_Pin = ss.SCL;
	GPIOB_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOB_init_struct.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(ss.GPIO, &GPIOB_init_struct);

	GPIOB_init_struct.GPIO_Pin = ss.SDA;
	GPIO_Init(ss.GPIO, &GPIOB_init_struct);

	// I2S needs Push Pull 
	// DACDAT
	GPIOB_init_struct.GPIO_Pin = GPIO_Pin_15;
	GPIOB_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(ss.GPIO, &GPIOB_init_struct);

	// LRC
	GPIOB_init_struct.GPIO_Pin = GPIO_Pin_12;
	GPIOB_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(ss.GPIO, &GPIOB_init_struct);

	// BCLK
	GPIOB_init_struct.GPIO_Pin = GPIO_Pin_13;
	GPIOB_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(ss.GPIO, &GPIOB_init_struct);

	I2C_InitTypeDef I2C2_init_struct;
	// Setup the I2C2 BUS properties
	I2C2_init_struct.I2C_Mode = I2C_Mode_I2C;
	I2C2_init_struct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C2_init_struct.I2C_ClockSpeed = 100000;
	// Setup I2C2 BUS master properties
	I2C2_init_struct.I2C_OwnAddress1 = 0;
	I2C2_init_struct.I2C_Ack = I2C_Ack_Enable;
	I2C2_init_struct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C2, &I2C2_init_struct);
	I2C_Cmd(I2C2, ENABLE);

	// init BCLK, LRC, DACDAT
	I2S_InitTypeDef I2S2_InitStructure;
	I2S2_InitStructure.I2S_Mode = I2S_Mode_MasterTx;
	I2S2_InitStructure.I2S_Standard = I2S_Standard_Phillips;
	I2S2_InitStructure.I2S_DataFormat = I2S_DataFormat_16b;
	I2S2_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Disable;
	I2S2_InitStructure.I2S_AudioFreq = I2S_AudioFreq_Default;
	I2S2_InitStructure.I2S_CPOL = I2S_CPOL_Low;
	I2S_Init(SPI2, &I2S2_InitStructure);


	///// i am not sure /////
	// SPI_Cmd(SPI2, ENABLE);
	I2S_Cmd(SPI2, ENABLE);
	SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);


	// calculate packet error checking
//	I2C_CalculatePEC(I2C2, ENABLE);

// receive interrupt ==> not using now
// NVIC_InitTypeDef NVIC_InitStructure;
// NVIC_InitStructure.NVIC_IRQChannelCmd = I2C2_EV_IRQn;
// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
// NVIC_Init(&NVIC_InitStructure);

// enable intterupt
//	I2C_ITConfig(I2C2, I2C_IT_EVT | I2C_IT_BUF, ENABLE);


}

void Sound_Run(void) {

}


void Sound_Test_init(void) {
	WM8978_Init();

	WM8978_SPKvol_Set(30);
	WM8978_HPvol_Set(30, 30);

	I2S2_TX_DMA_init(buf, buf, 70);
//	DMA_Cmd(DMA1_Channel4, ENABLE);



//	GPIO_InitTypeDef GPIOB_init_struct;
//
//	// DACDAT
//	GPIOB_init_struct.GPIO_Pin = GPIO_Pin_15;
//	GPIOB_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIOB_init_struct.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(ss.GPIO, &GPIOB_init_struct);

//	// BCLK
//	GPIOB_init_struct.GPIO_Pin = GPIO_Pin_13;
//	GPIO_Init(GPIOB, &GPIOB_init_struct);
////	GPIO_SetBits(GPIOB, GPIO_Pin_13);
//
//	GPIOB_init_struct.GPIO_Pin = GPIO_Pin_12;
//	GPIO_Init(GPIOB, &GPIOB_init_struct);

}

void Sound_Test_run(void) {
//	SPI_I2S_SendData(SPI2, 0x23);

	// debuging
//	uint8_t txe = SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE);
//	uint8_t udr = SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_OVR);
//	setLED(0, 0, udr, txe);
}

void I2C2_Stop() {
	I2C_GenerateSTOP(I2C2, ENABLE);
}

void I2C2_StartTransmission(uint8_t transmissionDirection, uint8_t slaveAddress) {
	// wait unitl i2c2 module is idle


	setLED(1, 0, 0, 1);
	while (I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
	setLED(0, 1, 1, 0);
	// generate the start condition
	I2C_GenerateSTART(I2C2, ENABLE);

	//
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));



	// send the address of the slave to be contacted
	I2C_Send7bitAddress(I2C2, slaveAddress, transmissionDirection);

	// if this is a write operation, set i2c for transmit
	if (transmissionDirection == I2C_Direction_Transmitter) {
		while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
			;
	}

	// of if a read operation, set i2c for receive
	if (transmissionDirection == I2C_Direction_Receiver) {
		while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
			;
	}
}

void I2C2_WriteData(uint8_t data) {
	// write the data on the bus
	I2C_SendData(I2C2, data);

	// wait until transmission is complete
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
		;
}

uint8_t I2C2_ReadData() {
	// Wait until receive is completed
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED))
		;
	uint8_t data;
	// read one byte of data from I2C2
	data = I2C_ReceiveData(I2C2);
	return data;

}

///////// ******* modify this!!! *********
// Sampling rate calculation formula: Fs = I2SxCLK / [256 * (2 * I2SDIV + ODD)]
// I2SxCLK = (HSE / pllm) * PLLI2SN / PLLI2SR
// General HSE = 8Mhz
// pllm: Sys_Clock_Set set in the time to determine, usually 8
// PLLI2SN: usually 192 ~ 432
// PLLI2SR: 2 ~ 7
// I2SDIV: 2 ~ 255
// ODD: 0/1
// I2S frequency division coefficient table @ pllm = 8, HSE = 8Mhz, vco input frequency of 1Mhz
// Table format: sample rate / 10, PLLI2SN, PLLI2SR, I2SDIV, ODD
const uint16_t I2S_PSC_TBL [][5] = {
	{ 800 , 256 , 5 , 12 , 1 },		 // 8Khz sample rate
	{ 1102 , 429 , 4 , 19 , 0 },		 // 11.025Khz sample rate
	{ 1600 , 213 , 2 , 13 , 0 },		 // 16Khz sample rate
	{ 2205 , 429 , 4 , 9 , 1 },		 // 22.05Khz sample rate
	{ 3200 , 213 , 2 , 6 , 1 },		 // 32Khz sample rate
	{ 4410 , 271 , 2 , 6 , 0 },		 // 44.1 Khz sample rate
	{ 4800 , 258 , 3 , 3 , 1 },		 // 48Khz sample rate
	{ 8820 , 316 , 2 , 3 , 1 },		 // 88.2Khz sample rate
	{ 9600 , 344 , 2 , 3 , 1 },  	 // 96Khz sample rate
	{ 17640 , 361 , 2 , 2 , 0 },  	 // 176.4Khz sample rate
	{ 19200 , 393 , 2 , 2 , 0 },  	 // 192Khz sample rate
};


// Set the sampling rate of IIS (@MCKEN)
// samplerate: sampling rate, unit: Hz
// Return value: 0, set successfully; 1, can not be set.
// uint8_t I2S2_SampleRate_Set(uint32_t samplerate)
// { 
// 	u8 i = 0 ;
// 	u32 tempreg = 0 ;
// 	samplerate /= 10 ; // 10 times smaller   
	
// 	for (i = 0; i < (sizeof(I2S_PSC_TBL)/10); i++) {
// 		// See if the sample rate can be changed
// 		if (samplerate == I2S_PSC_TBL[i][0]) break;
// 	}
 


// 	RCC_PLLI2SCmd(DISABLE); // Turn off PLLI2S first
// 	if (i == ( sizeof (I2S_PSC_TBL) / 10 )) return  1 ; / / searched too can not find
// 	RCC_PLLI2SConfig ((U32) I2S_PSC_TBL [I] [ . 1 ], (U32) I2S_PSC_TBL [I] [ 2 ]); // Set the frequency I2SxCLK (x = 2) is provided PLLI2SN PLLI2SR
 
// 	RCC-> CR | = 1 << 26 ;					 // Turn on the I2S clock
// 	while ((RCC-> CR & 1 << 27 ) == 0 );		 // Wait for the I2S clock to turn on successfully.
// 	tempreg = I2S_PSC_TBL [i] [ 3 ] << 0 ;	 // Set I2SDIV
// 	tempreg | = I2S_PSC_TBL [i] [ 3 ] << 8 ;	 // Set ODD bit
// 	tempreg | = 1 << 9 ;					 // MCKOE bit is enabled and MCK is output
// 	SPI2-> I2SPR = tempreg;			 // Set I2SPR register
// 	return  0 ;
// }  




// I2S2 TX DMA configuration
// Set to double buffering mode and turn DMA transfer complete interrupt
// buf0: M0AR address.
// buf1: M1AR address.
// num: the amount of data transferred each time
void I2S2_TX_DMA_init(u8 *buf0, u8 *buf1, u16 num) {
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	// DMA1 clock enable
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	DMA_DeInit(DMA1_Channel4);
	
	// // Waits for DMA1_Stream4 to be configurable
	// while ( DMA_GetCmdStatus (DMA1_Stream4)! = DISABLE) {} 
	// // Clear all interrupt flags on DMA1_Stream4	
	// DMA_ClearITPendingBit (DMA1_Stream4, DMA_IT_FEIF4 | DMA_IT_DMEIF4 | DMA_IT_TEIF4 | DMA_IT_HTIF4 | DMA_IT_TCIF4); 

	/* Configuring DMA Stream */
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&SPI2->DR; 
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)buf0; // DMA memory 0 address
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST; // memory to perhipheral mode
	DMA_InitStructure.DMA_BufferSize = num; 
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 16bit
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; // 16bit
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; // 
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
// 	  DMA_InitStructure. DMA_FIFOMode = DMA_FIFOMode_Disable; // Do not use FIFO mode        
//   DMA_InitStructure. DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
//   DMA_InitStructure. DMA_MemoryBurst = DMA_MemoryBurst_Single; // Peripheral burst single transfer
//   DMA_InitStructure. DMA_PeripheralBurst = DMA_PeripheralBurst_Single; // Memory Burst Single Transfer
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);

// 	DMA_DoubleBufferModeConfig (DMA1_Stream4, (u32) buf1, DMA_Memory_0); // Double-buffering mode configuration
 
//   DMA_DoubleBufferModeCmd (DMA1_Stream4, ENABLE); // double buffering mode on

	DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_Init(&NVIC_InitStructure);
}


// i2s dma callback function pointer
//void (* i2s_tx_callback) (void);
//
//
//void DMA1_Channel4_IRQn(void) {
//	if(DMA_GetITStatus(DMA1_Channel4, DMA_IT_TCIF4) == SET) {
//		DMA_ClearITPendingBit(DMA1_Channel4, DMA_IT_TCIF4);
//		i2s_tx_callback();
//	}
//
//}
