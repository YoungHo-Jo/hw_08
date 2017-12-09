// flash load ./a/Debug/a.axf
#include "init.h"
#include "lcd.h"
#include "Touch.h"
#include "touchSensor.h"
#include "pressureSensor.h"
#include "sound.h"
#include "piezo.h"
#include "timer.h"
#include "button.h"
#include "bluetooth.h"
#include "terminal.h"



// flash load "./hw_team08/Debug/hw_team08.axf"

// flash load ./a/Debug/a.axf
// flash load ./a/hw_08/flashclear.axf


int main(void) {
	// set system and set clock
	/* RCC init part */
	defaultSystemInit();
	LCD_Init();
	LCD_Clear(WHITE);
	T_RCC_Init();
	BT_RCC_Init();
//	Sound_RCC_Init();

	/* Configuration of GPIO, Timer ... */
	initLED();
	BT_Init();
	T_Init();
//	Sound_Init();

//	ADC_DMA_Config();
//	GPIO_Touch_Init_All();
//	Piezo_Config();
//	GPIO_Button_Init();

	/* Actual run part */
	BT_Run();
	T_Run();
//	Sound_Run();
//	Sound_Test_Init(); // if uncomment this, main will be stuck here
//	Init_Sound_Timer2();

	/* Reset Part */

	while(1) {
		BT_SendToTerminal();
		T_SendToBT();
	}
}



