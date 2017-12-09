/*
 * record.c


 *
 *  Created on: 2017. 12. 9.
 *      Author: hw_8
 */


#include "record.h"

extern uint32_t syllable;
extern int octave;

extern int record_idx;
extern int replay_idx;
extern int record_state;

/*
void Init_Record_Timer4() {
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	// Enable TIM2 Global Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  //NVIC ?縕ワ옙猿녿뎨�ⓦ끉�뺧옙占�

	// TIM2 Initialize
	TIM_TimeBaseStructure.TIM_Period = 1000 - 1; // 100kHz// 占쎈굝�ｏ옙�곷뎨?
	TIM_TimeBaseStructure.TIM_Prescaler = 1000; //
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //占쎌쥙猷욑옙占�?縕ワ옙猿녿뎨�ⓦ끉�뺧옙占�

	// TIM2 Enale
	TIM_Cmd(TIM4, ENABLE); //占쎌쥙猷욑옙占썽넫洹λ꼥嶺뚮∥梨울옙占쏙옙�좊즸占쎌늺��쭔袁좊윾?占쎈끂��占쎌쥙�ο㎖硫깅빝影�쪇��占�?占쎄쑴猷뉓짆�묓떐?
	TIM_ITConfig(TIM4, TIM_IT_Update | TIM_IT_CC1, ENABLE); // interrupt enable
}

void TIM4_IRQHandler(void) {
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
		if (record_state == 1) {
			syll_arr[record_idx] = syllable;
			oct_arr[record_idx++] = octave;
		} else if (record_state == 2) {
			syllable = syll_arr[replay_idx];
			octave = oct_arr[replay_idx++];
			if (replay_idx == record_idx) {
				replay_idx = record_idx = 0;
				record_state = 0;
			}
		}

		TIM_ClearITPendingBit(TIM4, TIM_IT_Update); // Clear the interrupt flag
	}
}
*/

void GPIO_Button_Init() {
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource11);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource12);


	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_InitStructure.EXTI_Line = EXTI_Line12;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI15_10_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line11) != RESET) {
		record_state = 1;
		record_idx = 0;
		LCD_ShowString(100, 200, "recording...   ", WHITE, BLACK);
		EXTI_ClearITPendingBit(EXTI_Line11);
	}
	else if (EXTI_GetITStatus(EXTI_Line12) != RESET) {
		record_state = 2;
		replay_idx = 0;
		LCD_ShowString(100, 200, "not recording  ", WHITE, BLACK);
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
}



