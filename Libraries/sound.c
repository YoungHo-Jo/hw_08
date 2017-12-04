#include "sound.h"

Sound_struct ss;

Sound_struct* Sound_Struct_init(void) {
	ss.SCL = GPIO_Pin_10;
	ss.SDA = GPIO_Pin_11;

	return &ss;
}

void Sound_RCC_init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
}

void Sound_init(void) {
	GPIO_InitTypeDef GPIOB_init_struct;

	// config I2C2 pins: SCL and SDA == GPIOB_Pin_10 and GPIOB_Pin_11
	GPIOB_init_struct.GPIO_Pin = ss.SCL | ss.SDA;
	GPIOB_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOB_init_struct.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &GPIOB_init_struct);

	I2C_InitTypeDef I2C2_init_struct;
	I2C2_init_struct.I2C_Mode = I2C_Mode_I2C;
	I2C2_init_struct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C2_init_struct.I2C_Ack = I2C_Ack_Enable;
	I2C2_init_struct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C2_init_struct.I2C_ClockSpeed = 20000;
	I2C_Init(I2C2, &I2C2_init_struct);

}

void Sound_Run(void) {
	I2C_Cmd(I2C2, ENABLE);
}
