#include "terminal.h"

Terminal_Struct * ts;

void Terminal_Struct_init() {
     ts = (Terminal_Struct *)malloc(sizeof(Terminal_Struct));
     ts->GPIO = GPIOA;
     ts->TX = GPIO_Pin_9;
     ts->RX = GPIO_Pin_10;
     ts->RX_Counter = 0;
}

void Terminal_Rcc_init() {
     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);


void Terminal_Init() {
     USART_InitTypeDef usart1_init_struct;
     GPIO_InitTypeDef gpioa_init_struct;
     NVIC_InitTypeDef nvic_init_struct;
     DMA_InitTypeDef DMA_InitStructure;

     Terminal_Rcc_Init();
     Terminal_Struct_Init();

     gpioa_init_struct.GPIO_Pin = ts->TX;
     gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
     gpioa_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
     GPIO_Init(GPIOA, &gpioa_init_struct);

     gpioa_init_struct.GPIO_Pin = ts->RX;
     gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
     gpioa_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_Init(GPIOA, &gpioa_init_struct);

     // USARTy_Tx_DMA_Channel (triggered by USARTy Tx event) Config
     DMA_DeInit(DMA1_Channel7);	
     DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;
     DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ts->RX_Buffer;
     DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
     DMA_InitStructure.DMA_BufferSize = TERMINAL_RX_BUFFER_SIZE;
     DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable
     DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
     DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
     DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
     DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
     DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
     DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
     DMA_Init(DMA1_Channel7, &DMA_InitStructure);

     usart1_init_struct.USART_BaudRate = 115200;
     usart1_init_struct.USART_WordLength = USART_WordLength_8b;
     usart1_init_struct.USART_StopBits = USART_StopBits_1;
     usart1_init_struct.USART_Parity = USART_Parity_No;
     usart1_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
     usart1_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
     USART_Init(USART1, &usart1_init_struct);

     nvic_init_struct.NVIC_IRQChannel = USART1_IRQn;
     nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
     nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 1;
     nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
     NVIC_Init(&nvic_init_struct);

     USART_DMACmd(USART2, USART_DMAReq_Tx | USART_DMAReq_Rx, ENABLE);
     USART_Cmd(USART1, ENABLE);
     USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

void USART1_IRQHandler() {
     if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
	  char c = USART_ReceiveData(USART1);

	  if (c == '\r' || c == '\n') {
	       ts->RX_Buffer[ts->RX_Counter++] = c;
	       DMA1_Channel7->CMAR = (uint32_t)ts->RX_Buffer;
    		DMA1_Channel7->CNDTR = ts->RX_Counter;
    		DMA_Cmd(DMA1_Channel7, ENABLE);
	       whlie (DMA_GetFlagStatus(DMA1_FLAG_TC7) == RESET){}
	       DMA_ClearITPendingBit(DMA1_IT_TC7);
	       DMA_Cmd(DMA1_Channel7, DISABLE);
	       ts->RX_Counter = 0;

	  } else if (ts->RX_Counter < TERMINAL_RX_BUFFER_SIZE) {
	       ts->RX_Buffer[ts->RX_Counter++] = c;
	       USART_SendData(USART1, c);
	       while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
	  }

	  USART_ClearITPendingBit(USART1, USART_IT_RXNE);
     }
}
