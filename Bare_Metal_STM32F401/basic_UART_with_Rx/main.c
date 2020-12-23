//APB1 bit 17: USART2 (coz that is diretly connected to the st-link)
//USART2 Tx and Rx connected to PA2 and PA3
//We will only use Rx i.e. PA3 in this project
//for GPIOA clock enable set the 1st bit of RCC->AHB1ENR
//AF7 for USART1..2

#include "stm32f4xx.h"                  // Device header

void USART_init(void);
uint8_t USART_read(void);
void USART2_write(uint16_t ch);
void USART2_str(uint8_t	*arg);
void delayms(int delay);
void led_play(int value);

char ch;
uint8_t TxData[21] = "Character Received\r\n";
uint8_t data[19] = "USART Initialized\r\n";
int main()
{
	//RCC->AHB1ENR |= 1;					//Enable clock access to port A
	//GPIOA->MODER |= 0x400;				//Set pin as output
	
	USART_init();
	
	USART2_str(data);
	led_play(13);
	while(1)
	{
		ch = (char)USART_read();
		USART2_write(ch);
		led_play(ch);
	}
}

void USART_init()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	//RCC->AHB1ENR |= (1<<0);
	//RCC->APB1ENR |= (1<<17);
	
	//GPIOA->AFR[0] = GPIO_AFRL_AFRL7_0|GPIO_AFRL_AFRL7_1;
	GPIOA->AFR[0] = 0x7700;				//Alernate function 7 for USART2 for PA2 and PA3
	GPIOA->MODER |= 0x0080;				//SET PA3 to alternate function
	GPIOA->MODER |= 0x0020;				//SET PA2 to alternate function
	GPIOA->MODER |= 0x0400;				//Set PA5 to output
	
	//USART2->BRR = 16000000 / 115200;	//9600 @16MHz
	USART2->BRR  = 0x008B;				//115200 @16MHz	
	/*USART2->CR1 |= 0x0004;				//ENABLE Rx
	USART2->CR1 |= 0x0008;				//ENABLE Tx, Rx, 8-bit data
	USART2->CR1 |= 0x2000;				//ENABLE USART2*/
	USART2->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
}

uint8_t USART_read()
{
	while(!(USART2->SR & USART_SR_RXNE)){}		//wait until character arrives
	return USART2->DR;
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

void led_play(int value)
{
	value %= 16;
	for(; value>0; value--)
	{
		GPIOA->BSRR = 0x20;				//Turn on the LED
		delayms(100);
		GPIOA->BSRR = 0x00200000;		//Turn off the LED
		delayms(100);
	}
	delayms(400);
}

void delayms(int delay)
{
	int i;
	for(;delay>0; delay--)
	{
		for(i = 0; i < 3195; i++);
	}
}
