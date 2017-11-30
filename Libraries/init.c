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
		//Flash LATENCY�� �����ϴºκ� -> FLASH_ACR�κп��� flash�� System Clock�� �ӵ��� �����ִ� ����!
		//������ �ʿ����
		FLASH->ACR &= (uint32_t) ((uint32_t) ~FLASH_ACR_LATENCY);
		FLASH->ACR |= (uint32_t) FLASH_ACR_LATENCY_1;

		/* HCLK = SYSCLK */
		//���� SystemClock�� HCLK, PCLK1,PCLK2�� ���� ����(/1)
		//=> �츮�� ������� ���·�!
		RCC->CFGR |= (uint32_t) RCC_CFGR_HPRE_DIV2;

		/* PCLK2 = HCLK */
		RCC->CFGR |= (uint32_t) RCC_CFGR_PPRE2_DIV2;

		/* PCLK1 = HCLK */
		RCC->CFGR |= (uint32_t) RCC_CFGR_PPRE1_DIV1;

		/* Configure PLLs ------------------------------------------------------*/
		/* PLL configuration: PLLCLK = ???? */
		//�� clock tree���� PREDIV1SCH�� ���� PREDIV1�� PLLMUL�� �����ؼ� System clock�� 40����!
		//�̹� CFGR2���� ������ ���� �̿��Ͽ� ����!!
		RCC->CFGR &= (uint32_t) ~(RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC
				| RCC_CFGR_PLLMULL);
		RCC->CFGR |= (uint32_t) (RCC_CFGR_PLLXTPRE_PREDIV1
				| RCC_CFGR_PLLSRC_PREDIV1 |
				RCC_CFGR_PLLMULL5);

		/* PLL2 configuration: PLL2CLK = ???? */
		/* PREDIV1 configuration: PREDIV1CLK = ???? */
		//HSE���� ������ frequency = 25MHz
		//HSE -> CFGR2 -> CFGR1 -> System���ϋ� PREDIV2�� PLL2MUL�� �� �����ؼ� CFGR1����!
		RCC->CFGR2 &= (uint32_t) ~(RCC_CFGR2_PREDIV2 | RCC_CFGR2_PLL2MUL |
		RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC);
		RCC->CFGR2 |= (uint32_t) (RCC_CFGR2_PREDIV2_DIV5 | RCC_CFGR2_PLL2MUL8 |
		RCC_CFGR2_PREDIV1SRC_PLL2 | RCC_CFGR2_PREDIV1_DIV5);

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

		/* Select PLL as system clock source */
		RCC->CFGR &= (uint32_t) ((uint32_t) ~(RCC_CFGR_SW));
		RCC->CFGR |= (uint32_t) RCC_CFGR_SW_PLL;

		/* Wait till PLL is used as system clock source */
		while ((RCC->CFGR & (uint32_t) RCC_CFGR_SWS) != (uint32_t) 0x08) {
		}
	} else { /* If HSE fails to start-up, the application will have wrong clock
	 configuration. User can add here some code to deal with this error */
	}


    // ���ó�� �˼� ���� RCC ========================= //
	// RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPDEN; // enable PORT_D PORT_A

	// GPIOD->CRL = GPIO_CRL_MODE2_0; // set PD2 to MODE2 // output
	// GPIOD->CRL = GPIO_CRL_MODE2_0; // set PD2 to MODE2 // output

	// GPIOA->CRH = GPIO_CRH_CNF8_1 | GPIO_CRH_MODE8;
	// RCC->CFGR |= RCC_CFGR_MCO_SYSCLK;
    // ============================================ //
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

