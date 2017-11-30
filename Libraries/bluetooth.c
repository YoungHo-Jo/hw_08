#include "bluetooth.h"
#include "lcd.h"
BT_Struct bs;
u8 x = 10;
u16 y = 10;
void BT_RCC_init() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	BT_Struct_Init();
}

BT_Struct* BT_Struct_Init() {
	bs.BT_TX = GPIO_Pin_2;
	bs.BT_RX = GPIO_Pin_3;
	bs.BT_GPIO = GPIOA;
	bs.BT_RX_Counter = 0;

	return &bs;
}

void BT_init() {
	USART_InitTypeDef USART2_init_struct;
	GPIO_InitTypeDef GPIOA_init_struct;
	NVIC_InitTypeDef NVIC_init_struct;

	// Output GPIO pin init
	GPIOA_init_struct.GPIO_Pin = bs.BT_TX;
	GPIOA_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOA_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(bs.BT_GPIO, &GPIOA_init_struct);

	// Input GPIO pin init
	GPIOA_init_struct.GPIO_Pin = bs.BT_RX;
	GPIOA_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOA_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(bs.BT_GPIO, &GPIOA_init_struct);

	// USART2 init
	USART2_init_struct.USART_BaudRate = 9600;
	USART2_init_struct.USART_WordLength = USART_WordLength_8b;
	USART2_init_struct.USART_StopBits = USART_StopBits_1;
	USART2_init_struct.USART_Parity = USART_Parity_No;
	USART2_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART2_init_struct.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;

	// NVIC init for Interrupt handler
	NVIC_init_struct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_init_struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_init_struct.NVIC_IRQChannelPreemptionPriority = 10;
	NVIC_init_struct.NVIC_IRQChannelSubPriority = 10;
	NVIC_Init(&NVIC_init_struct);

	USART_Init(USART2, &USART2_init_struct);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}

void BT_Run() {
	USART_Cmd(USART2, ENABLE);
}

void USART2_IRQHandler() {
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
				// receive a char from sender
				char c = USART_ReceiveData(USART2);

	//			if (c == '\r' || c == '\n') {
	//				uint16_t i = 0;
	//				for (i = 0; i < bs.BT_RX_Counter; i++) {
	//					// send content of the buffer
	//					USART_SendData(USART1, bs.BT_RX_Buffer[i]);
	//					while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
	//				}
	//				// rest the counter of the buffer
	//				bs.BT_RX_Counter = 0;
	//
	//			} else if (bs.BT_RX_Counter < USART_RX_BUFFER_SIZE) {
	//				// store to the buffer
	//				bs.BT_RX_Buffer[bs.BT_RX_Counter] = (uint16_t) c;
	//				// increase the counter of the buffer
	//				bs.BT_RX_Counter++;
	//				while (!USART_GetFlagStatus(USART2, USART_FLAG_TXE));
	//			}

				// send to terminal
				USART_SendData(USART1, c);
				while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE));

				// clear USART2 interrupt bit
				USART_ClearITPendingBit(USART2, USART_IT_RXNE);
			}
}

void BT_IRQHandler(void) {

}
