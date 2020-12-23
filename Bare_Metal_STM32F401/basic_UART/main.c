//APB1 bit 17: USART2 (coz that is diretly connected to the st-link)
//USART2 Tx and Rx connected to PA2 and PA3
//for GPIOA clock enable set the 1st bit of RCC->AHB1ENR
//AF7 for USART1..2

	

#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common

void USART2_init(void);
void USART2_write(uint16_t ch);
void USART2_str(uint8_t	*arg);
void delayms(int delay);

uint32_t freq;

uint8_t TxData[13] = "Hello World\r\n";

int main()
{
	USART2_init();
	freq = HAL_RCC_GetSysClockFreq();
	while(1)
	{
		//USART2_write('H');
		//USART2_write('i');
		//USART2_write('\n');
		//HAL_Delay(1000);
		USART2_str(TxData);
		delayms(1000);
	}
}

void USART2_init()
{
	RCC->APB1ENR |= (1<<17);
	RCC->AHB1ENR |= (1<<0);
	
	GPIOA->AFR[0] = 0x0700;
	GPIOA->MODER |= 0x0020;	//SET PA2 to alternate function

	
	USART2->BRR = 16000000 / 115200;	//115200 @16MHz
	USART2->CR1 |= 0x0008;	//ENABLE Tx, Rx, 8-bit data
	USART2->CR1 |= 0x2000;
}

void USART2_write(uint16_t ch)
{
	//wait while the Tx buffer is empty
	while(!(USART2->SR & (1U<<7)));
	USART2->DR = (ch & (uint16_t)0x01FF);
}

void USART2_str(uint8_t	*arg)
{
	while(*arg != '\0')
	USART2_write(*arg++);
}

void delayms(int delay)
{
	int i;
	for(;delay>0; delay--)
	{
		for(i = 0; i < 3195; i++);
	}
}
