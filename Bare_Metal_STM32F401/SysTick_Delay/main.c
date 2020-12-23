#include "stm32f4xx.h"                  // Device header


void precise_delay(uint32_t ms);

int main()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |= (1<<10);				//PA5 as output or 0x400
	//GPIOA->MODER |= GPIO_MODER_MODER5_0;
	while(1)
	{
		GPIOA->ODR ^= GPIO_ODR_OD5;
		precise_delay(1000);
	}
	
}

void precise_delay(uint32_t ms)
{
	SysTick->LOAD = 16000-1;												//Reload with the number of clocks per millisecond
	SysTick->VAL = 0;														//Clear current value register
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;	//Enable SysTick
	
	for (uint32_t i = 0; i < ms; i++)
	{
		//Wait until the count flag is set
		while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
	}
	SysTick->CTRL = 0;		//Reset the systick
}
