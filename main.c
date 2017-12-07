/*
 * main.c
 *
 *  Created on: 2017. 12. 7.
 *      Author: owk
 */


#include "init.h"
#include "bluetooth.h"
#include "lcd.h"
#include "Touch.h"
#include "touchSensor.h"
#include "terminal.h"
#include "bluetooth.h"


int main(void) {
	defaultSystemInit();

	LCD_Init();
	LCD_Clear(WHITE);
	LCD_ShowNum(100, 200, 234, 5, WHITE, BLUE);
	GPIO_touch_init_all();

	BT_Init();
	Terminal_Init();


	init_Timer2();

	while (1) {

	}

}
