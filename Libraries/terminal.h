#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#define TERMINAL_RX_BUFFER_SIZE 20

typedef struct {
	uint16_t TX;
	uint16_t RX;
	GPIO_TypeDef* GPIO;
	char RX_Buffer[TERMINAL_RX_BUFFER_SIZE];
	uint16_t RX_Counter;
} Terminal_Struct;

void Terminal_Struct_init(Terminal_Struct *);
void Terminal_Rcc_init(Terminal_Struct *);
void Terminal_init(Terminal_Struct *);
void Terminal_IRQHandler(Terminal_Struct *);
void USART1_IRQHandler(void);

void Terminal_Run();


#endif
