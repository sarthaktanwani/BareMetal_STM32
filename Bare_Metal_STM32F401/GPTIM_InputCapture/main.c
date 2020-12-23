#include "stm32f4xx.h"                  // Device header

int main()
{
	RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER 	= (1<<11);					//Set PA5 as alternate function
	GPIOA->AFR[0] 	= 0x100000;				//Set pin of AF1 for TIM2 channel 1
	
	RCC->APB1ENR 	|= RCC_APB1ENR_TIM2EN;
	TIM2->PSC 		= 1600 - 1;
	TIM2->ARR 		= 10000;
	TIM2->CCMR1 	= 0x30;					//Set output to toggle on match
	TIM2->CCR1 		= 0;					// Set match mode
	TIM2->CCER		|= 1;					//Enable ch1 compare mode
	TIM2->CNT		= 0;					//clear counter
	TIM2->CR1		= 1;					//ENABLE Tim2
	
	//Configure PA6 as input of TIM3 CH1
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	while(1)
	{
		
	}
}