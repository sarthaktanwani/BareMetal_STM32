#include "stm32f4xx.h"                  // Device header

int main()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |= (1<<10);				//PA5 as output
	
	//Configure SysTick to generate 100ms delay
	//for 1 sec -> 16 x 10^6 cycles
	// for 100 ms or 1/10th of a second -> 16 x 10^6 /10 = 1600000 cycles
	//Enter the number of cycles -1 into the SysTick Load register
	SysTick->LOAD = 1600000-1;
	SysTick->VAL = 0;
	SysTick->CTRL = 5;
	
	while(1)
	{
		//check if count flag is set
		if(SysTick->CTRL & 0x10000)
		{
			GPIOA->ODR ^= GPIO_ODR_OD5;
		}
	}
}