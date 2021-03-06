#include "timer.h"
#include "piezo.h"
#include "pressureSensor.h"
#include "touchSensor.h"

extern uint32_t syllable;
extern int octave;
extern int pressure[];

uint32_t cur_syll;
int color[12] = { WHITE, CYAN, BLUE, RED, MAGENTA, LGRAY, GREEN, YELLOW, BROWN,
BRRED, GRAY };

char syll_arr[RECORD_LEN];
char oct_arr[RECORD_LEN];

int record_idx = 0;
int replay_idx = 0;
int record_state = 0;
int tick = 0;

void Init_Sound_Timer2() {
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/* Enable TIM2 Global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 100;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 100;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  //NVIC ?縕ワ옙猿녿뎨�ⓦ끉�뺧옙占�

	/* TIM2 Initialize */
	TIM_TimeBaseStructure.TIM_Period = 50 - 1; // 100kHz// 占쎈굝�ｏ옙�곷뎨?
	TIM_TimeBaseStructure.TIM_Prescaler = 10; //
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //占쎌쥙猷욑옙占�?縕ワ옙猿녿뎨�ⓦ끉�뺧옙占�

	/* TIM2 Enale */

}
void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {

		if (tick == 1000) {
			tick = 0;
			LCD_ShowString(150, 100, "hello", WHITE, BLACK);
			LCD_ShowString(150, 120, "hello", WHITE, BLACK);
			LCD_ShowString(150, 140, "hello", WHITE, BLACK);
			LCD_ShowString(150, 160, "hello", WHITE, BLACK);
			LCD_ShowString(150, 180, "hello", WHITE, BLACK);

			if (record_state == 1) {
				syll_arr[record_idx] = syllable;
				oct_arr[record_idx++] = octave;
			} else if (record_state == 2) {
				if (replay_idx == record_idx) {
					replay_idx = 0;
					record_state = 0;
				}
				syllable = syll_arr[replay_idx];
				octave = oct_arr[replay_idx++];
			}
		}
		tick++;
		cur_syll = (cur_syll) ? cur_syll : syllable;
		setSound(cur_syll);
		cur_syll = cur_syll & (cur_syll - 1);
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // Clear the interrupt flag
	}
}

void Timer_Start() {
	TIM_Cmd(TIM2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_Update | TIM_IT_CC1, ENABLE); // interrupt enable
}

void Timer_Stop() {
	TIM_Cmd(TIM2, DISABLE);
	TIM_ITConfig(TIM2, TIM_IT_Update | TIM_IT_CC1, DISABLE); // interrupt enable
}

