#include "terminal.h"

Terminal_Struct ts;

Terminal_Struct* Terminal_Struct_init() {
	ts.GPIO = GPIOA;
	ts.TX = GPIO_Pin_9;
	ts.RX = GPIO_Pin_10;
	ts.RX_Counter = 0;
	ts.readyToSend = FALSE;

	return &ts;
}

void Terminal_Rcc_init() {
	RCC_APB2PeriphClockCmd(
	RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
}

void Terminal_init() {
	USART_InitTypeDef usart1_init_struct;
	GPIO_InitTypeDef gpioa_init_struct;
	NVIC_InitTypeDef nvic_init_struct;

	gpioa_init_struct.GPIO_Pin = ts.TX;
	gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	gpioa_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &gpioa_init_struct);

	gpioa_init_struct.GPIO_Pin = ts.RX;
	gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	gpioa_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpioa_init_struct);

	USART_Cmd(USART1, ENABLE);
	usart1_init_struct.USART_BaudRate = 115200;
	usart1_init_struct.USART_WordLength = USART_WordLength_8b;
	usart1_init_struct.USART_StopBits = USART_StopBits_1;
	usart1_init_struct.USART_Parity = USART_Parity_No;
	usart1_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart1_init_struct.USART_HardwareFlowControl =
	USART_HardwareFlowControl_None;

	nvic_init_struct.NVIC_IRQChannel = USART1_IRQn;
	nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvic_init_struct);

	USART_Init(USART1, &usart1_init_struct);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}
void Terminal_IRQHandler() {
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
			char c = USART_ReceiveData(USART1);

			if (c == '\r' || c == '\n') {
				Terminal_storeInBuf(c);
				ts.readyToSend = TRUE;
			} else if (ts.RX_Counter < TERMINAL_RX_BUFFER_SIZE) {
				Terminal_storeInBuf(c);

				USART_SendData(USART1, c);
				while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
			}

			USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		}
}

void USART1_IRQHandler(void) {
	Terminal_IRQHandler();
}

void Terminal_Run() {
	USART_Cmd(USART1, ENABLE);
}

void Terminal_sendToBT() {
	if (ts.readyToSend == TRUE) {
		int i = 0;
		for (i = 0; i < ts.RX_Counter; i++) {
			USART_SendData(USART2, ts.RX_Buffer[i]);
			while (!USART_GetFlagStatus(USART2, USART_FLAG_TXE))
				;
		}
		ts.RX_Counter = 0;

		ts.readyToSend = FALSE;
	}
}

void Terminal_storeInBuf(uint16_t c) {
	ts.RX_Buffer[ts.RX_Counter++] = c;
}
