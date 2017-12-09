#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "lcd.h"

void Button_Config() {
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable GPIOA clock */

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);

	/* Configure PA.00 pin as input floating */

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* Connect EXTI0 Line to PA.00 pin */

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);

	/* Configure EXTI0 line */

	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI0 Interrupt to the lowest priority */

	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_Init(&NVIC_InitStructure);

}

void EXTI3_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line3) != RESET) {
		LCD_ShowString(150, 150, "hello", BLACK, WHITE);
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}

void EXTI4_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line4) != RESET) {
		LCD_ShowString(150, 150, "world", BLACK, WHITE);
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}

