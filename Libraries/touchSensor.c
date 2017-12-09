#include "touchSensor.h"
#include "piezo.h"

uint32_t syllable = 0;

void EXTI1_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line1) != RESET) {
	        syllable ^= 1;
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

void EXTI9_5_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line7) != RESET) {
	        syllable ^= (1 << 1);
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
	else if (EXTI_GetITStatus(EXTI_Line9) != RESET) {
			syllable ^= (1 << 2);
			EXTI_ClearITPendingBit(EXTI_Line9);
	}
}

void GPIO_Touch_Init(GPIO_TypeDef * GPIO_x,
		             uint16_t GPIO_Pin_x,
		             uint8_t GPIO_PortSource_x,
		             uint8_t GPIO_PinSource_x,
		             uint32_t EXTI_Line_x,
		             uint8_t EXTI_x_IRQn)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIO_x, &GPIO_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSource_x, GPIO_PinSource_x);

	EXTI_InitStructure.EXTI_Line = EXTI_Line_x;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI_x_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void GPIO_Touch_Init_All() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

	GPIO_Touch_Init(GPIOB, GPIO_Pin_1, GPIO_PortSourceGPIOB, GPIO_PinSource1, EXTI_Line1, EXTI1_IRQn);
	GPIO_Touch_Init(GPIOB, GPIO_Pin_7, GPIO_PortSourceGPIOB, GPIO_PinSource7, EXTI_Line7, EXTI9_5_IRQn);
	GPIO_Touch_Init(GPIOB, GPIO_Pin_9, GPIO_PortSourceGPIOB, GPIO_PinSource9, EXTI_Line9, EXTI9_5_IRQn);
}
