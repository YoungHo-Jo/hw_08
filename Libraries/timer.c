/*
 * timer.c
 *
 *  Created on: 2017. 12. 7.
 *      Author: hw_4
 */

#include "timer.h"

extern int syllable;
extern uint32_t pressure[];

int color[12] = { WHITE, CYAN, BLUE, RED, MAGENTA, LGRAY, GREEN, YELLOW, BROWN,BRRED, GRAY };

void init_Timer2() {
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/* TIM2 Clock Enable */

	/* Enable TIM2 Global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  //NVIC 珥덇린��

	/* TIM2 Initialize */
	TIM_TimeBaseStructure.TIM_Period = 200 - 1; // 100kHz// 二쇨린
	TIM_TimeBaseStructure.TIM_Prescaler = 1000 - 1; //
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //��엫 珥덇린��

	/* TIM2 Enale */
	TIM_Cmd(TIM2, ENABLE); //��씠癒멸� 媛�뱷李⑤㈃ �명꽣�쏀듃 諛쒖깮
	TIM_ITConfig(TIM2, TIM_IT_Update | TIM_IT_CC1, ENABLE); // interrupt enable
}
void TIM2_IRQHandler(void) //�몃뱾���⑥닔�먯꽌  TIM_GetITStatus(TIM2,TIM_IT_Update)瑜��듯빐���명꽣�쏀듃 �뚮옒洹멸�  set �섏뼱�덈뒗吏��뺤씤�섍퀬 �닿� 留뚮뱺 蹂�닔 利앷��쒕떎.
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		//LCD_ShowString(100, 200, "abcd", WHITE, BLUE);
		LCD_ShowNum(100, 200, syllable, 5, WHITE, BLUE);
		LCD_ShowNum(0, 100, pressure[0], 5, WHITE, BLUE);
		LCD_ShowNum(40, 100, pressure[1], 5, WHITE, BLUE);
		LCD_ShowNum(80, 100, pressure[2], 5, WHITE, BLUE);
		//LCD_ShowNum(120, 100, pressure[3], 5, WHITE, BLUE);
		//LCD_ShowNum(160, 100, pressure[4], 5, WHITE, BLUE);
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // Clear the interrupt flag
	}
}
