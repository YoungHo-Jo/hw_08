/*
 * main.c
 *
 *  Created on: 2017. 11. 27.
 *      Author: hw_8
 */

#include "init.h"
#include "touchSensor.h"
#include "lcd.h"
#include "Touch.h"


int main() {
	// set system and set clock
	defaultSystemInit();



	GPIO_touch_init_all();
	init_Timer2();

	LCD_Init();
	Touch_Configuration();
	LCD_Clear(WHITE);
	LCD_ShowNum(100, 200, 234, 5, WHITE, BLUE);
	while (1) {

	}
}