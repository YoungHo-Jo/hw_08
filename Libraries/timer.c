/*
 * timer.c
 *
 *  Created on: 2017. 12. 7.
 *      Author: hw_4
 */

#include "timer.h"

extern uint32_t pressure[];
extern int pressure_cnt;
extern int time;
extern int scale;
extern const int minPressure;
extern int recording;

int color[12] = { WHITE, CYAN, BLUE, RED, MAGENTA, LGRAY, GREEN, YELLOW, BROWN,BRRED, GRAY };
uint32_t sound = 0;
uint32_t record_arr[10000];

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
	NVIC_Init(&NVIC_InitStructure);  //NVIC ?λ뜃由곤옙占?

	/* TIM2 Initialize */
	TIM_TimeBaseStructure.TIM_Period = 200 - 1; // 100kHz// 雅뚯눊由?
	TIM_TimeBaseStructure.TIM_Prescaler = 1000 - 1; //
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //占쏙옙???λ뜃由곤옙占?

	/* TIM2 Enale */
	TIM_Cmd(TIM2, ENABLE); //占쏙옙?좂솒硫몌옙 揶쏉옙諭뤄㎕?ㅳ늺 占쎈챸苑ｏ옙???獄쏆뮇源?
	TIM_ITConfig(TIM2, TIM_IT_Update | TIM_IT_CC1, ENABLE); // interrupt enable
}
void TIM2_IRQHandler(void) //占쎈챶諭억옙占쏙옙?λ땾占쎈Ŋ苑? TIM_GetITStatus(TIM2,TIM_IT_Update)?쒙옙占쎈벏鍮먲옙占쏙옙紐낃숲占쎌???占쎈슢?믤뉩硫몌옙  set 占쎌꼷堉깍옙?덈뮉筌욑옙占쎈벡?ㅿ옙?랁?占쎈떯占?筌띾슢諭?癰귨옙??筌앹빓占쏙옙?뺣뼄.
{
        
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
	        setSound();
	        LCD_ShowNum(0, 100, pressure[0], 5, WHITE, BLUE);
	        LCD_ShowNum(40, 100, pressure[1], 5, WHITE, BLUE);
	        LCD_ShowNum(80, 100, pressure[2], 5, WHITE, BLUE);
	        LCD_ShowNum(120, 100, pressure[3], 5, WHITE, BLUE);
	        LCD_ShowNum(160, 100, pressure[4], 5, WHITE, BLUE);
	        LCD_ShowNum(200, 100, pressure[5], 5, WHITE, BLUE);
	        LCD_ShowNum(240, 100, pressure[6], 5, WHITE, BLUE);

		
	        LCD_ShowNum(0, 50, sound, 5, WHITE, BLUE);
	        LCD_ShowNum(80, 50, recording, 5, WHITE, BLUE);

		if (recording) {
		     record_arr[time++] = sound;
		     if (time == max_record_time)
			  record = 0;
		}
		 
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // Clear the interrupt flag
	}
}


void setSound()
{
     int i;
     int minVol = 3;
     sound = 0;
    
     for (i=0; i<pressure_cnt; i++) {
	 if (minPressure < pressure[i]) {
	      sound |= 1<<i+scale*7;
	 }
     }
}
     

