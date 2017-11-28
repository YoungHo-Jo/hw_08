#include "bluetooth.h"

void BT_RCC_init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
}

void BT_init() {
    USART_InitTypeDef USART2_init_struct;
	GPIO_InitTypeDef GPIOA_init_struct;
	NVIC_InitTypeDef NVIC_init_struct;

    // Output GPIO pin init
	GPIOA_init_struct.GPIO_Pin = BT_TX;
	GPIOA_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOA_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(BT_GPIO, &GPIOA_init_struct);

    // Input GPIO pin init
	GPIOA_init_struct.GPIO_Pin = BT_RX;
	GPIOA_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOA_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(BT_GPIO, &GPIOA_init_struct);

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

void BT_Run() {
    USART_Cmd(USART2, ENABLE);
}

void BT_IRQHandler(void) {
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
        // receive a char from sender
        char c = USART_ReceiveData(USART2);

		if (c == '\r') {
            uint16_t i = 0;
			for(i = 0; i < BT_RX_Counter; i++) {
                // send content of the buffer
				USART_SendData(USART2, BT_RX_Buffer[i]);
				while(!USART_GetFlagStatus(USART2, USART_FLAG_TXE));
			}
            // rest the counter of the buffer
			BT_RX_Counter = 0;

			USART_SendData(USART2, '\n');
			while(!USART_GetFlagStatus(USART2, USART_FLAG_TXE));
		} else if (BT_RX_Counter < USART_RX_BUFFER_SIZE){
            // store to the buffer
			BT_RX_Buffer[BT_RX_Counter] = (uint16_t) c;
            // increase the counter of the buffer
			BT_RX_Counter++;
			while(!USART_GetFlagStatus(USART2, USART_FLAG_TXE));
		}

        // clear USART2 interrupt bit
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
}
