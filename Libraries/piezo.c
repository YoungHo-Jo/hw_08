#include "piezo.h"



void PIEZO_RCC_init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
}
void PIEZO_init(void) {

    /* GPIO Setting */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* TIM2 Configuration */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 0xf;
    TIM_TimeBaseStructure.TIM_Prescalar = 0xf;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    /* TIM2 TRGO selection */
    TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);

    /* DAC Channel Configuration */
    DAC_InitTypeDef DAC_InitStructure;
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Triangle;
    DAC_InitStructure.DAC_LFSUnmask_TriangleAmplitude = DAC_TriangleAmplitude_4095;
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
    DAC_Init(DAC_Channel_1, &DAC_InitStructure);

    /* DAC Channel2 Configuration */
    DAC_InitStructure.DAC_LFSUnmask_TriangleAmplitude = DAC_TriangleAmplitude_1023;
    DAC_Init(DAC_Channel_2, &DAC_InitStructure);

    /* Enable DAC Channel1 */
    // Once the DAC channel1 is enabled, PA,04 is automatically connected to the DAC convertor
    DAC_Cmd(DAC_Channel_1, ENABLE);

    /* Enable DAC Channel2 */
    // Once the DAC channel2 is enabled, PA.05 is automatically connected to the DAC convertor
    DAC_Cmd(DAC_Channel_2, ENABLE);

    /* Set DAC dual channel DHR12RD register */
    DAC_SetDualChannelData(DAC_Align_12b_R, 0x100, 0x100);

    /* TIM2 enable counter */
    TIM_Cmd(TIM2, ENABLE);
}
void Delay(__IO uint32_t nCount) {
    for(; nCount != 0; nCount--);
}
