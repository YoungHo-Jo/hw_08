#include "init.h"
#include "bluetooth.h"
#include "lcd.h"
#include "Touch.h"
#include "touchSensor.h"
#include "terminal.h"
#include "sound.h"

// flash load "./hw_team08/Debug/hw_team08.axf"
// flash load "./hw_team08/flashClear.axf"

// flash load ./b/Debug/b.axf

void initLED(void);
void setLED(uint8_t, uint8_t, uint8_t, uint8_t);

int main(void) {
	// set system and set clock
	// =========== RCC init part ===========
	defaultSystemInit();
	LCD_Init();
	Terminal_Rcc_init();
	BT_RCC_init();
	Sound_RCC_init();

	// =========== get struct =============
	Terminal_Struct* ts = Terminal_Struct_init();
	BT_Struct* bs = BT_Struct_Init();
	Sound_struct* ss = Sound_Struct_init();

	LCD_Clear(WHITE);
	LCD_ShowNum(100, 200, 234, 5, WHITE, BLUE);

	//============ config init ==============
	initLED();
//	BT_init();
//	Terminal_init();
	Sound_init();
	// gpio touch init와 init timer를 lcd init 보다 할 경우 lcd init이 제대로 이루어지지 않으며
	// 계속 1의 값이 들어옴
//	GPIO_touch_init_all();

	// run
//	BT_Run();
//	Terminal_Run();
	Sound_Run();

	Sound_Test_init();
	// TIMER 작동시 블루투스에서 보드로 가는 USART의 전송을 타이머가 뺏어가버리기 때문에
	// 온전하지 못한 데이터가 전송되어 잘못된 문자가 터미널에 찍힘을 확인하였음
//	init_Timer2();
	while (1) {
		Terminal_sendToBT();
		BT_sendToTerminal();

		//// test
		Sound_Test_run();
		////

		uint8_t bclk = GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_13);
		uint8_t dacdat = GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_15);
		uint8_t lrc = GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12);
		setLED(bclk, lrc, dacdat, 1);
	}
}

void initLED() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

}

void setLED(uint8_t one, uint8_t two, uint8_t three, uint8_t four) {
	if (one) {
		GPIO_SetBits(GPIOD, GPIO_Pin_2);
	} else {
		GPIO_ResetBits(GPIOD, GPIO_Pin_2);
	}
	if (two) {
		GPIO_SetBits(GPIOD, GPIO_Pin_3);
	} else {
		GPIO_ResetBits(GPIOD, GPIO_Pin_3);
	}

	if (three) {
		GPIO_SetBits(GPIOD, GPIO_Pin_4);
	} else {
		GPIO_ResetBits(GPIOD, GPIO_Pin_4);
	}
	if (four) {
		GPIO_SetBits(GPIOD, GPIO_Pin_7);
	} else {
		GPIO_ResetBits(GPIOD, GPIO_Pin_7);
	}
}
