#include "stm32f0xx.h"                  // Device header
int main()
{
	RCC->AHBENR |= (1<<17);
	RCC->AHBENR |= (1<<18);
	
	GPIOA->MODER |= (1<<8);
	//GPIOB->MODER &= ~((1<<0)|(1<<1));		//redundant command
	GPIOB->PUPDR |= (1<<3);
	while(1)
	{
		if(GPIOB->IDR & 0x02)				//when PB1 is high or default in PullUp
		{
			GPIOA->BRR = (1<<4);			//pin PA4 pe 0 yaani Yes LED
		}
		else								//when PB1 is low or default in Pull Down
		{
			GPIOA->BSRR = (1<<4);			//pin PA4 pe 1 yaaani No LED
		}
	}
}