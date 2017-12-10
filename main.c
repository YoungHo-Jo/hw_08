// flash load ./a/Debug/a.axf
#include "init.h"
#include "bluetooth.h"
#include "lcd.h"
#include "Touch.h"
#include "touchSensor.h"
#include "pressureSensor.h"
#include "terminal.h"
#include "sound.h"
#include "piezo.h"
#include "timer.h"



// flash load "./hw_team08/Debug/hw_team08.axf"

// flash load ./a/Debug/a.axf
// flash load ./a/hw_08/flashclear.axf


int main(void) {
	// set system and set clock
	/* RCC init part */
	defaultSystemInit();
	LCD_Init();
	Terminal_Rcc_init();
	BT_RCC_init();
	Sound_RCC_init();

	/* Get structs */
	Terminal_Struct* ts = Terminal_Struct_init();
	BT_Struct* bs = BT_Struct_Init();
	Sound_struct* ss = Sound_Struct_init();

	

	/* Configuration of GPIO, Timer ... */
	initLED();
	BT_init();
	Terminal_init();
	Sound_init();
	init_Timer2();
	GPIO_touch_init_all();

	/* Acutal run part */
	BT_Run();
	Terminal_Run();
	Sound_Run();
	Sound_Test_init();

	/* Reset Part */
	LCD_Clear(WHITE);
	LCD_ShowNum(100, 200, 234, 5, WHITE, BLUE);

	while(1) {
		BT_sendToTerminal();
		Terminal_sendToBT();
	}
}



