#include "init.h"
#include "bluetooth.h"
#include "lcd.h"
#include "Touch.h"
#include "touchSensor.h"
#include "terminal.h"

// flash load "./hw_team08/Debug/hw_team08.axf"
// flash load "./hw_team08/flashClear.axf"

int main(void) {
	// set system and set clock
	// =========== RCC init part ===========
	defaultSystemInit();
	LCD_Init();
	Terminal_Rcc_init();
	BT_RCC_init();

	// =========== get struct =============
	Terminal_Struct* ts = Terminal_Struct_init();
	BT_Struct* bs = BT_Struct_Init();

	LCD_Clear(WHITE);
	LCD_ShowNum(100, 200, 234, 5, WHITE, BLUE);

	//============ config init ==============
	BT_init();
	Terminal_init();
	// gpio touch init와 init timer를 lcd init 보다 할 경우 lcd init이 제대로 이루어지지 않으며
	// 계속 1의 값이 들어옴
	GPIO_touch_init_all();


	// run
	BT_Run();
	Terminal_Run();
	// TIMER 작동시 블루투스에서 보드로 가는 USART의 전송을 타이머가 뺏어가버리기 때문에
	// 온전하지 못한 데이터가 전송되어 잘못된 문자가 터미널에 찍힘을 확인하였음
//	init_Timer2();

	while (1) {
		Terminal_sendToBT();
		BT_sendToTerminal();
//		if (ts->readyToSend == TRUE) {
//			int i;
//
//			for (i = 0; i < ts->RX_Counter; i++) {
//				USART_SendData(USART2, ts->RX_Buffer[i]);
//				while (!USART_GetFlagStatus(USART2, USART_FLAG_TXE));
//			}
//			ts->RX_Counter = 0;
//			i = 0;
//			ts->readyToSend = FALSE;
//		}
	}
}
