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
	// gpio touch init�� init timer�� lcd init ���� �� ��� lcd init�� ����� �̷������ ������
	// ��� 1�� ���� ����
	GPIO_touch_init_all();


	// run
	BT_Run();
	Terminal_Run();
	// TIMER �۵��� ����������� ����� ���� USART�� ������ Ÿ�̸Ӱ� ��������� ������
	// �������� ���� �����Ͱ� ���۵Ǿ� �߸��� ���ڰ� �͹̳ο� ������ Ȯ���Ͽ���
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
