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


int main(void) {
	// set system and set clock
	// =========== RCC init part ===========
	defaultSystemInit();
//	LCD_Init();
//	Terminal_Rcc_init();
//	BT_RCC_init();
	Sound_RCC_init();

	// =========== get struct =============
//	Terminal_Struct* ts = Terminal_Struct_init();
//	BT_Struct* bs = BT_Struct_Init();
	Sound_struct* ss = Sound_Struct_init();

//	LCD_Clear(WHITE);
//	LCD_ShowNum(100, 200, 234, 5, WHITE, BLUE);

	//============ config init ==============
	initLED();
//	BT_init();
//	Terminal_init();
	setLED(1, 1, 1, 1);
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
//		Terminal_sendToBT();
//		BT_sendToTerminal();

		//// test
		Sound_Test_run();
		////
		uint8_t bclk = I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY);
		uint8_t dacdat = GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_15);
		uint8_t lrc = GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12);
		uint8_t txe = SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY);
		setLED(bclk, lrc, dacdat, txe);
	}
}

