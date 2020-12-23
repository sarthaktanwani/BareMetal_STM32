//PA4 active low apparently
//RCC->AHBENR
//GPIOx_ODR

#include "stm32f0xx.h"                  // Device header

void delayms(int delay);
int main()
{
	RCC->AHBENR 	|= (1<<17);
	GPIOA->MODER 	|= (1<<8);
	while(1)
	{
		GPIOA->ODR |= (1<<4);
		delayms(50);
		GPIOA->ODR &= ~(1<<4);
		delayms(50);
	}
}

void delayms(int delay)
{
	int i;
	for(; delay > 0; delay--)
		for(i = 0; i<3195; i++);
}
