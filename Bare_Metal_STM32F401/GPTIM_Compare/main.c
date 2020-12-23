#include "stm32f4xx.h"                  // Device header

//Toggle LED at 20Hz using Timer 2 compare mode or a time delay of 50 ms
int main()
{
	RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER 	|= 0x800; 					//sets PA5 to alternate function
	
	GPIOA->AFR[0] 	= 0x100000;				//AF1 for Timer 2 for pin PA5
	RCC->APB1ENR 	|= RCC_APB1ENR_TIM2EN;
	TIM2->PSC 		= 800-1;
	TIM2->ARR 		= 1000;
	TIM2->CCMR1		= 0x30;					//Set output to toggle on match
	TIM2->CCR1 		= 0;					// Set match mode
	TIM2->CCER		|= 1;					//Enable ch1 compare mode
	TIM2->CNT		= 0;					//clear counter 
	TIM2->CR1		= 1;					//ENABLE Tim2
	while(1);
}
