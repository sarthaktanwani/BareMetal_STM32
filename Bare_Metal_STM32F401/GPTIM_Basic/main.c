//we will use timer2; APB1 bus for clock

#include "stm32f4xx.h"                  // Device header

int main()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |= (1<<10);
	
	//Timer Config
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->PSC = 1600-1;			//Divide Timer clock source(saem as system clock source) by 1600; 
								//PSC register is 16-bit wide so max value you can input here is 65535
	TIM2->ARR = 10000-1;		//Divided once again by 10,000 so 16000 000 / 1600 = 10000 / 10000 = 1 Hz
	TIM2->CNT = 0;
	TIM2->CR1 = TIM_CR1_CEN; 	//Counter/Timer enable
	while(1)
	{
		while((TIM2->SR & TIM_SR_UIF)) //TIM_SR_UIF-> Update Interrupt Flag
		{
			TIM2->SR &= ~TIM_SR_UIF;
			GPIOA->ODR ^= GPIO_ODR_OD5;
		}
	}
}
