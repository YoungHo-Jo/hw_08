#include "touchSensor.h"

const int SCALE_UP = GPIO_Pin_1;
const int SCALE_DOWN = GPIO_Pin_3;
const int RECORD_START = GPIO_Pin_5;
const int RECORD_END   = GPIO_Pin_7;
const int VOLUM_UP     = GPIO_Pin_8;
const int VOLUM_DOWN   = GPIO_Pin_9;

int time = 0;
int scale = 0;
const int MAX_SCALE = 1;
int recording = 0;

void EXTI1_IRQHandler(void) {
     if (EXTI_GetITStatus(EXTI_Line1) != RESET) {
	  //scale up
	  if (scale < MAX_SCALE)
	       scale++;
	  EXTI_ClearITPendingBit(EXTI_Line1);
     }
}

void EXTI3_IRQHandler(void) {
     if (EXTI_GetITStatus(EXTI_Line3) != RESET) {
	  //scale down 
	  if (0 < scale)
	       scale--;
	  EXTI_ClearITPendingBit(EXTI_Line3);
     }
}

void EXTI9_5_IRQHandler(void) {
     if (EXTI_GetITStatus(EXTI_Line5) != RESET) {
	  //record start
	  time = 0;
	  recording = 1;
	  EXTI_ClearITPendingBit(EXTI_Line5);
     }
     else if (EXTI_GetITStatus(EXTI_Line7) != RESET) {
	  //record end
	  recording = 0;
	  EXTI_ClearITPendingBit(EXTI_Line7);
     }
     else if (EXTI_GetITStatus(EXTI_Line8) != RESET) {
	  //volum up
	  EXTI_ClearITPendingBit(EXTI_Line8);
     }
     else if (EXTI_GetITStatus(EXTI_Line9) != RESET) {
	  //volum down
	  EXTI_ClearITPendingBit(EXTI_Line9);
     }
}

GPIO_setting_data get_GPIO_Setting_Data(uint16_t key) {
     GPIO_setting_data gpio_setting_data;
     switch(key) {
     case SCALE_UP :
	  gpio_setting_data.pin_src = GPIO_PinSource1;
	  gpio_setting_data.exti_line = EXTI_Line1;
	  gpio_setting_data.exti_irqn = EXTI1_IRQn;
	  gpio_setting_data.port_src = GPIO_PortSourceGPIOB;
	  gpio_setting_data.GPIOx = GPIOB;
	  break;
     case SCALE_DOWN :
	  gpio_setting_data.pin_src = GPIO_PinSource3;
	  gpio_setting_data.exti_line = EXTI_Line3;
	  gpio_setting_data.exti_irqn = EXTI3_IRQn;
	  gpio_setting_data.port_src = GPIO_PortSourceGPIOB;
	  gpio_setting_data.GPIOx = GPIOB;
	  break;
     case VOLUM_UP :
	  gpio_setting_data.pin_src = GPIO_PinSource8;
	  gpio_setting_data.exti_line = EXTI_Line8;
	  gpio_setting_data.exti_irqn = EXTI9_5_IRQn;
	  gpio_setting_data.port_src = GPIO_PortSourceGPIOB;
	  gpio_setting_data.GPIOx = GPIOB;
	  break;
     case VOLUM_DOWN :
	  gpio_setting_data.pin_src = GPIO_PinSource9;
	  gpio_setting_data.exti_line = EXTI_Line9;
	  gpio_setting_data.exti_irqn = EXTI9_5_IRQn;
	  gpio_setting_data.port_src = GPIO_PortSourceGPIOB;
	  gpio_setting_data.GPIOx = GPIOB;
	  break;
     case RECORD_END :
	  gpio_setting_data.pin_src = GPIO_PinSource7;
	  gpio_setting_data.exti_line = EXTI_Line7;
	  gpio_setting_data.exti_irqn = EXTI9_5_IRQn;
	  gpio_setting_data.port_src = GPIO_PortSourceGPIOB;
	  gpio_setting_data.GPIOx = GPIOB;
	  break;
     case RECORD_START :
	  gpio_setting_data.pin_src = GPIO_PinSource5;
	  gpio_setting_data.exti_line = EXTI_Line5;
	  gpio_setting_data.exti_irqn = EXTI9_5_IRQn;
	  gpio_setting_data.port_src = GPIO_PortSourceGPIOB;
	  gpio_setting_data.GPIOx = GPIOB;
	  break;
     }
     return gpio_setting_data;
}

void GPIO_touch_init(uint16_t key) {
     GPIO_InitTypeDef GPIO_InitStructure;
     EXTI_InitTypeDef EXTI_InitStructure;
     NVIC_InitTypeDef NVIC_InitStructure;
     GPIO_setting_data gpio_setting_data = get_GPIO_Setting_Data(key);
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); 

     GPIO_InitStructure.GPIO_Pin = key; 
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
     GPIO_Init(gpio_setting_data.GPIOx, &GPIO_InitStructure);
     GPIO_EXTILineConfig(gpio_setting_data.port_src, gpio_setting_data.pin_src);

     EXTI_InitStructure.EXTI_Line = gpio_setting_data.exti_line;
     EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
     EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
     EXTI_InitStructure.EXTI_LineCmd = ENABLE;
     EXTI_Init(&EXTI_InitStructure);

     NVIC_InitStructure.NVIC_IRQChannel = gpio_setting_data.exti_irqn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
}

void GPIO_touch_init_all() {
     GPIO_touch_init(SCALE_UP);
     GPIO_touch_init(SCALE_DOWN);
     GPIO_touch_init(VOLUM_UP);
     GPIO_touch_init(VOLUM_DOWN);
     GPIO_touch_init(RECORD_START);
     GPIO_touch_init(RECORD_END);
}
<<<<<<< HEAD

void TIM2_IRQHandler(void) //핸들러 함수에서  TIM_GetITStatus(TIM2,TIM_IT_Update)를 통해서 인터럽트 플래그가  set 되어있는지 확인하고 내가 만든 변수 증가한다.
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		//LCD_ShowString(100, 200, "abcd", WHITE, BLUE);
		LCD_ShowNum(100, 200, syllable, 5, WHITE, BLUE);
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // Clear the interrupt flag
	}
}

void init_Timer2() {
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/* TIM2 Clock Enable */

	/* Enable TIM2 Global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 10;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  //NVIC 초기화

	/* TIM2 Initialize */
	TIM_TimeBaseStructure.TIM_Period = 200 - 1; // 100kHz// 주기
	TIM_TimeBaseStructure.TIM_Prescaler = 1000 - 1; //
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //타임 초기화

	/* TIM2 Enale */
	TIM_Cmd(TIM2, ENABLE); //타이머가 가득차면 인터럽트 발생
	TIM_ITConfig(TIM2, TIM_IT_Update | TIM_IT_CC1, ENABLE); // interrupt enable
}





=======
>>>>>>> terminal
