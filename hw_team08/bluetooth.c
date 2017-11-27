#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#define USART_RX_BUFFER_SIZE 20

const uint16_t USART_TX = GPIO_Pin_2;
const uint16_t USART_RX = GPIO_pin_3;
const GPIO_TypeDef* USART_GPIO = GPIOA;
char USART_RX_Buffer[USART_RX_BUFFER_SIZE];
uint16_t USART_RX_Counter = 0;


void USART2_RCC_init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
}

void USART2_init() {
    USART_InitTypeDef USART2_init_struct;
	GPIO_InitTypeDef GPIOA_init_struct;
	NVIC_InitTypeDef NVIC_init_struct;

    // Output GPIO pin init
	GPIOA_init_struct.GPIO_Pin = USART_TX;
	GPIOA_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOA_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(USART_GPIO, &GPIOA_init_struct);

    // Input GPIO pin init
	GPIOA_init_struct.GPIO_Pin = USART_RX;
	GPIOA_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOA_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART_GPIO, &GPIOA_init_struct);

    // USART2 init
	USART2_init_struct.USART_BaudRate = 115200;
	USART2_init_struct.USART_WordLength = USART_WordLength_8b;
	USART2_init_struct.USART_StopBits = USART_StopBits_1;
	USART2_init_struct.USART_Parity = USART_Parity_No;
	USART2_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART2_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    // NVIC init for Interrupt handler
	NVIC_init_struct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_init_struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_init_struct);

	USART_Init(USART2, &USART2_init_struct);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}

void USART2_Run() {
    USART_Cmd(USART2, ENABLE);
}

void USART2_IRQHandler(void) {
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
        char c = USART_ReceiveData(USART2);

		uint16_t i = 0;
		if (c == '\r') {
			for(i = 0; i < USART_RX_Counter; i++) {
				USART_SendData(USART2, USART_RX_Buffer[i]);
				while(!USART_GetFlagStatus(USART2, USART_FLAG_TXE));
			}
			USART_RX_Counter = 0;

			USART_SendData(USART1, '\n');
			while(!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
		} else if (USART_RX_Counter < USART_RX_BUFFER_SIZE){
			USART_RX_Buffer[USART_RX_Counter] = (uint16_t)c;
			USART_RX_Counter++;
			while(!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
		}
	}
}