#include "sound.h"

Sound_struct ss;

Sound_struct* Sound_Struct_init(void) {
	ss.SCL = GPIO_Pin_10;
	ss.SDA = GPIO_Pin_11;
	ss.GPIO = GPIOB;
	return &ss;
}

void Sound_RCC_init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); // 필요한지 정확하게 모르겠음

}

void Sound_init(void) {
	GPIO_InitTypeDef GPIOB_init_struct;

	// config I2C2 pins: SCL and SDA == GPIOB_Pin_10 and GPIOB_Pin_11
	GPIOB_init_struct.GPIO_Pin = ss.SCL | ss.SDA;
	GPIOB_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOB_init_struct.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(ss.GPIO, &GPIOB_init_struct);

	I2C_InitTypeDef I2C2_init_struct;
	// Setup the I2C2 BUS properties
	I2C2_init_struct.I2C_Mode = I2C_Mode_I2C;
	I2C2_init_struct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C2_init_struct.I2C_ClockSpeed = 20000;
	// Setup I2C2 BUS master properties
	I2C2_init_struct.I2C_OwnAddress1 = I2C2_MASTER_ADDR;
	I2C2_init_struct.I2C_Ack = I2C_Ack_Enable;
	I2C2_init_struct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C2, &I2C2_init_struct);

	// calculate packet error checking
	I2C_CalculatePEC(I2C2, ENABLE);


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
	I2C_Cmd(I2C2, ENABLE);
}

void Sound_Test_init(void) {
	WM8978_Init();

	WM8978_SPKvol_Set(60);

	GPIO_InitTypeDef GPIOB_init_struct;

	// DACDAT
	GPIOB_init_struct.GPIO_Pin = GPIO_Pin_15;
	GPIOB_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOB_init_struct.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(ss.GPIO, &GPIOB_init_struct);

}

void Sound_Test_run(void) {
	GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_SET);
}


void I2C2_Stop() {
	I2C_GenerateSTOP(I2C2, ENABLE);
}

void I2C2_StartTransmission(uint8_t transmissionDirection, uint8_t slaveAddress) {
	// wait unitl i2c2 module is idle
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));

	// generate the start condition
	I2C_GenerateSTART(I2C2, ENABLE);

	//
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));

	// send the address of the slave to be contacted
	I2C_Send7bitAddress(I2C2, slaveAddress << 1, transmissionDirection);

	// if this is a write operation, set i2c for transmit
	if (transmissionDirection == I2C_Direction_Transmitter) {
		while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	}

	// of if a read operation, set i2c for receive
	if (transmissionDirection == I2C_Direction_Receiver) {
		while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	}
}

void I2C2_WriteData(uint8_t data) {
	// write the data on the bus
	I2C_SendData(I2C2, data);

	// wait until transmission is complete
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}

uint8_t I2C2_ReadData() {
	// Wait until receive is completed
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
	uint8_t data;
	// read one byte of data from I2C2
	data = I2C_ReceiveData(I2C2);
	return data;

}
