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

		// gpio touch init와 init timer를 lcd init 보다 할 경우 lcd init이 제대로 이루어지지 않으며
		// 계속 1의 값이 들어옴
		GPIO_touch_init_all();
		BT_Run();
		init_Timer2();

		while (1) {

		}

}
