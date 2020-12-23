// APB bus bit 14 for UART (register: APB2ENR)
//in stm32f030 PA2 is USART1_TX and PA3 is USART1_RX
//for GPIOA clock enable set the 17th bit of RCC->AHBENR
//in order to use the GPIO PA2 and PA3 as USART pins you need to set them to alternate function AF1 
//through the GPIOx_AFRL and GPIOx_AFRH (Alternate Function Register; High and Low) 
//to enable clock to GPIOA set the 17th bit of AHBENR register from RCC
//to ensure that the transmit data register is empty, use the bit 7 of Interrupt and Status Register
//to trasmit a byte through USART, we use the USART_TDR register

#include "stm32f0xx.h"                  // Device header
void USART1_write(int x);
void USART1_init(void);
void delayms(int);
int main()
{
	USART1_init();
	while(1)
	{
		USART1_write('H');
		USART1_write('i');
		delayms(100);
	}
}

void USART1_init(void)
{
	RCC->APB2ENR	|= (1<<14);
	RCC->AHBENR		|= (1<<17);
	
	GPIOA->AFR[0]	|= (1<<8)|(1<<12);		//the video guy is doing GPIOA->AFR[0] |= 0x700 for some reason
	GPIOA->MODER	|= (1<<5)|(1<<7);		//setting the GPIO mode to alternate function for PA2 and PA3		
	
	//USART1->BRR		= 0x0683;				//9600 @16MHz (as per the video; I don't know how)
	USART1->BRR		= 480000 / 96;			//as per the data sheet so I trust this more
	USART1->CR1 = USART_CR1_TE | USART_CR1_UE; /* (2) */
	//USART1->CR1		= 0x0008;				//setting the TE bit; Transmitter Enable bit
	//USART1->CR1		= 0x0001;				//setting the UE bit or the USART Enable bit
	//It may seem better to modify the CR1 register in a single statement (writing to it as 0x0009) but it 
	//would be wrong as it is advisable to do all the setup/initializing before actually enabling USART(that is
	//done in the last statement)
}

void USART1_write(int ch)
{
	int send;
	if ((USART1->ISR & USART_ISR_TC) == USART_ISR_TC)
	{
		if (send == sizeof(ch))
		{
			send=0;
			USART1->ICR |= USART_ICR_TCCF; /* Clear transfer complete flag */
		}
		else
		{
			/* clear transfer complete flag and fill TDR with a new char */
			USART1->TDR = ch;
		}
	}
	//int a = USART_ISR_TC;
	/*while(!(USART1->ISR & (1<<7)));			//wait while the TX buffer is empty
	USART1->TDR = (ch & 0xFF);		*/		//ANDing with 0xff to ensure that a byte value is assigned to TDR register
}

void delayms(int delay)
{
	int i;
	for(; delay > 0; delay--)
		for(i = 0; i < 3195; i++);
}
