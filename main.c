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
	// gpio touch init�� init timer�� lcd init ���� �� ��� lcd init�� ����� �̷������ ������
	// ��� 1�� ���� ����
//	GPIO_touch_init_all();

	// run
//	BT_Run();
//	Terminal_Run();
	Sound_Run();

	Sound_Test_init();
	// TIMER �۵��� ����������� ����� ���� USART�� ������ Ÿ�̸Ӱ� ��������� ������
	// �������� ���� �����Ͱ� ���۵Ǿ� �߸��� ���ڰ� �͹̳ο� ������ Ȯ���Ͽ���
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

