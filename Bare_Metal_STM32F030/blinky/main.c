//PA5 for LED
//AHB1
//RCC->AHB1ENR
//GPIOx_MODER
//GPIOx_ODR

#include "stm32f4xx.h"                  // Device header
void delayms(int delay);
int main(void)
{
	RCC->AHB1ENR |= 1;					// ENABLE GPIOA clock
	GPIOA->MODER = 0x400;
	GPIOA->MODER |= (1<<10);
	while(1)
	{
		GPIOA->ODR |= (1<<5);
		delayms(100);
		GPIOA->ODR &= ~(1<<5);
		delayms(100); 
	}

}

void delayms(int delay)
{
	int i;
	for(; delay>0; delay--)
		for(i = 0; i<3195; i++);
}
