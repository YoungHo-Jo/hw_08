/*
 * init.c
 *
 *  Created on: 2017. 11. 27.
 *      Author: hw_8
 */

#include "init.h"

void defaultSystemInit() {
	SysInit();
	SetSysClock();
}

void SetSysClock(void) {
	volatile uint32_t StartUpCounter = 0, HSEStatus = 0;

	/* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
	/* Enable HSE */
	RCC->CR |= ((uint32_t) RCC_CR_HSEON);

	/* Wait till HSE is ready and if Time out is reached exit */
	do {
		HSEStatus = RCC->CR & RCC_CR_HSERDY;
		StartUpCounter++;
	} while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

	if ((RCC->CR & RCC_CR_HSERDY) != RESET) {
		HSEStatus = (uint32_t) 0x01;
	} else {
		HSEStatus = (uint32_t) 0x00;
	}

	if (HSEStatus == (uint32_t) 0x01) {
		/* Enable Prefetch Buffer */
		FLASH->ACR |= FLASH_ACR_PRFTBE;

		/* Flash 0 wait state */
		//Flash LATENCY를 조절하는부분 -> FLASH_ACR부분에서 flash와 System Clock의 속도를 맞춰주는 역할!
		//수정할 필요없음
		FLASH->ACR &= (uint32_t) ((uint32_t) ~FLASH_ACR_LATENCY);
		FLASH->ACR |= (uint32_t) FLASH_ACR_LATENCY_1;

		/* HCLK = SYSCLK */
		//현재 SystemClock과 HCLK, PCLK1,PCLK2은 같은 상태(/1)
		//=> 우리가 만들려는 상태로!
		RCC->CFGR |= (uint32_t) RCC_CFGR_HPRE_DIV2;

		/* PCLK2 = HCLK */
		RCC->CFGR |= (uint32_t) RCC_CFGR_PPRE2_DIV2;

		/* PCLK1 = HCLK */
		RCC->CFGR |= (uint32_t) RCC_CFGR_PPRE1_DIV1;

		/* Configure PLLs ------------------------------------------------------*/
		/* PLL configuration: PLLCLK = ???? */
		//앞 clock tree에서 PREDIV1SCH를 거쳐 PREDIV1과 PLLMUL를 조정해서 System clock을 40으로!
		//이미 CFGR2에서 조절한 값을 이용하여 조절!!
		RCC->CFGR &= (uint32_t) ~(RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC
				| RCC_CFGR_PLLMULL);
		RCC->CFGR |= (uint32_t) (RCC_CFGR_PLLXTPRE_PREDIV1
				| RCC_CFGR_PLLSRC_PREDIV1 |
				RCC_CFGR_PLLMULL5);

		/* PLL2 configuration: PLL2CLK = ???? */
		/* PREDIV1 configuration: PREDIV1CLK = ???? */
		//HSE에서 들어오는 frequency = 25MHz
		//HSE -> CFGR2 -> CFGR1 -> System순일떄 PREDIV2와 PLL2MUL를 잘 조절해서 CFGR1으로!
		RCC->CFGR2 &= (uint32_t) ~(RCC_CFGR2_PREDIV2 | RCC_CFGR2_PLL2MUL |
		RCC_CFGR2_PLL3MUL | RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC);
		RCC->CFGR2 |= (uint32_t) (RCC_CFGR2_PREDIV2_DIV5 | RCC_CFGR2_PLL2MUL8
				| RCC_CFGR2_PLL3MUL8 | RCC_CFGR2_PREDIV1SRC_PLL2 | RCC_CFGR2_PREDIV1_DIV5);

		/* Enable PLL2 */
		RCC->CR |= RCC_CR_PLL2ON;
		/* Wait till PLL2 is ready */
		while ((RCC->CR & RCC_CR_PLL2RDY) == 0) {
		}

		/* Enable PLL */
		RCC->CR |= RCC_CR_PLLON;

		/* Wait till PLL is ready */
		while ((RCC->CR & RCC_CR_PLLRDY) == 0) {
		}

		/* Enable PLL3 */
		RCC->CR |= RCC_CR_PLL3ON;
		/* Wait till PLL2 is ready */
		while ((RCC->CR & RCC_CR_PLL3RDY) == 0) {
		}

		/* Select PLL as system clock source */
		RCC->CFGR &= (uint32_t) ((uint32_t) ~(RCC_CFGR_SW));
		RCC->CFGR |= (uint32_t) RCC_CFGR_SW_PLL;

		/* Wait till PLL is used as system clock source */
		while ((RCC->CFGR & (uint32_t) RCC_CFGR_SWS) != (uint32_t) 0x08) {
		}
	} else { /* If HSE fails to start-up, the application will have wrong clock
	 configuration. User can add here some code to deal with this error */
	}
	RCC->CFGR |= RCC_CFGR_MCO_SYSCLK;
}

void SysInit(void) {
	/* Set HSION bit */
	/* Internal Clock Enable */
	RCC->CR |= (uint32_t) 0x00000001;

	/* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
	RCC->CFGR &= (uint32_t) 0xF0FF0000;

	/* Reset HSEON, CSSON and PLLON bits */
	RCC->CR &= (uint32_t) 0xFEF6FFFF;

	/* Reset HSEBYP bit */
	RCC->CR &= (uint32_t) 0xFFFBFFFF;

	/* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
	RCC->CFGR &= (uint32_t) 0xFF80FFFF;

	/* Reset PLL2ON and PLL3ON bits */
	RCC->CR &= (uint32_t) 0xEBFFFFFF;

	/* Disable all interrupts and clear pending bits  */
	RCC->CIR = 0x00FF0000;

	/* Reset CFGR2 register */
	RCC->CFGR2 = 0x00000000;
}

void initLED() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

}

void setLED(uint8_t one, uint8_t two, uint8_t three, uint8_t four) {
	if (one) {
		GPIO_SetBits(GPIOD, GPIO_Pin_2);
	} else {
		GPIO_ResetBits(GPIOD, GPIO_Pin_2);
	}
	if (two) {
		GPIO_SetBits(GPIOD, GPIO_Pin_3);
	} else {
		GPIO_ResetBits(GPIOD, GPIO_Pin_3);
	}

	if (three) {
		GPIO_SetBits(GPIOD, GPIO_Pin_4);
	} else {
		GPIO_ResetBits(GPIOD, GPIO_Pin_4);
	}
	if (four) {
		GPIO_SetBits(GPIOD, GPIO_Pin_7);
	} else {
		GPIO_ResetBits(GPIOD, GPIO_Pin_7);
	}
}

