#include "piezo.h"
#include "pressureSensor.h"

#define PCLK2 20000000

extern int pressure[];

const int INIT_PERIOD = PCLK2/262;

const uint16_t DO = PCLK2/(262*1000);
const uint16_t RE = PCLK2/(294*1000);
const uint16_t MI = PCLK2/(330*1000);
const uint16_t FA = PCLK2/(349*1000);
const uint16_t SO = PCLK2/(392*1000);
const uint16_t LA = PCLK2/(440*1000);
const uint16_t TI = PCLK2/(494*1000);

const uint16_t period_arr[7] = {DO, RE, MI, FA, SO, LA, TI};
int octave = 0;

void Piezo_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	TIM_TimeBaseStructure.TIM_Period = INIT_PERIOD;
	TIM_TimeBaseStructure.TIM_Prescaler = 1000;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3, ENABLE);

	TIM_Cmd(TIM3, ENABLE);
}
  

void setSound(uint32_t syll)
{
  int i;
  for (i=0; i<7; i++) {
    if ((syll >> i) & 1) {
      TIM3->ARR = period_arr[i] >> octave;
      TIM3->CCR3 = (TIM3->ARR/10)*3;//pressure[i];
      return;
    }
  }
  TIM3->CCR3 = 0;
}

