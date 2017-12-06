#include "bluetooth.h"

BT_Struct bs;

void BT_RCC_Init() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
}

void BT_Struct_Init() {
	bs.GPIO = GPIOA;
	bs.TX = GPIO_Pin_2;
	bs.RX = GPIO_Pin_3;
	bs.RX_Counter = 0;
}

void BT_Init() {
	USART_InitTypeDef USART2_init_struct;
	GPIO_InitTypeDef GPIOA_init_struct;
	NVIC_InitTypeDef NVIC_init_struct;
	DMA_InitTypeDef DMA_InitStructure;

	BT_RCC_Init();
	BT_Struct_Init();

	// Output GPIO pin init
	GPIOA_init_struct.GPIO_Pin = bs.TX;
	GPIOA_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOA_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(bs.GPIO, &GPIOA_init_struct);

	// Input GPIO pin init
	GPIOA_init_struct.GPIO_Pin = bs.RX;
	GPIOA_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOA_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(bs.GPIO, &GPIOA_init_struct);


/*	DMA_DeInit(DMA1_Channel4);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) &USART1->DR;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) bs.RX_Buffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = BT_RX_BUFFER_SIZE;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);
*/

	// USART2 init
	USART2_init_struct.USART_BaudRate = 9600;
	USART2_init_struct.USART_WordLength = USART_WordLength_8b;
	USART2_init_struct.USART_StopBits = USART_StopBits_1;
	USART2_init_struct.USART_Parity = USART_Parity_No;
	USART2_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART2_init_struct.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_Init(USART2, &USART2_init_struct);

	// NVIC init for Interrupt handler
	NVIC_init_struct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_init_struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_init_struct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_init_struct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_init_struct);

	//USART_DMACmd(USART1, USART_DMAReq_Tx | USART_DMAReq_Rx, ENABLE);
	USART_Cmd(USART2, ENABLE);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}

void USART2_IRQHandler(void) {
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
		// receive a char from sender
		uint16_t c = USART_ReceiveData(USART2);
		int i;
		if (c == '\r' || c == '\n') {
			bs.RX_Buffer[bs.RX_Counter++] = c;

			for (i=0; i<bs.RX_Counter; i++) {
				USART_SendData(USART1, c);
				while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE)) {}
			}

			/*
			DMA1_Channel4->CMAR = (uint32_t) bs.RX_Buffer;
			DMA1_Channel4->CNDTR = bs.RX_Counter;
			DMA_Cmd(DMA1_Channel4, ENABLE);
			while (DMA_GetFlagStatus(DMA1_FLAG_TC4) == RESET) {}
			DMA_ClearITPendingBit(DMA1_IT_TC4);
			DMA_Cmd(DMA1_Channel4, DISABLE);
			*/

			bs.RX_Counter = 0;
		} else if (bs.RX_Counter < BT_RX_BUFFER_SIZE) {
			bs.RX_Buffer[bs.RX_Counter++] = c;
		}

		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
}
