#include "init.h"
#include "bluetooth.h"
#include "lcd.h"
#include "Touch.h"
#include "touchSensor.h"

// flash load "./hw_team08/Debug/hw_team08.axf"
// flash load "./hw_team08/flashClear.axf"


int main(void) {
	// set system and set clock
		defaultSystemInit();
		LCD_Init();
		BT_RCC_init();

		LCD_Clear(WHITE);
		LCD_ShowNum(100, 200, 234, 5, WHITE, BLUE);

		BT_init();

		// gpio touch init�� init timer�� lcd init ���� �� ��� lcd init�� ����� �̷������ ������
		// ��� 1�� ���� ����
		GPIO_touch_init_all();
		BT_Run();
		init_Timer2();

		while (1) {

		}

}
