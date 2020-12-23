#include "stm32f4xx.h"                  // Device header
#include <stdio.h>
void USART_init(void);
//int USART_read(void);
//int USART2_write(int);

int main()
{
	int n;
	char str[100];
	USART_init();
	printf("Hello from the other side\r\n");
	fprintf(stdout,"test for stdout\r\n");
	fprintf(stderr,"test for stderr\r\n");
	while(1)
	{
		printf("How old are you? ");
		scanf("%d", &n);
		printf("Your age is: %d\r\n", n);
		printf("Enter your first name: ");
		gets(str);
		printf("I like your style, ");
		puts(str);
		printf("\r\n");
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
	GPIOA->MODER |= 0x00A0;				//Set both PA2 & PA3 to alternate function
	//GPIOA->MODER |= 0x0400;				//Set PA5 to output
	
	USART2->BRR  = 16000000 / 9600;				//9600 @16MHz or 0x0683	
	
	//USART2->CR1 |= 0x000C;				//ENABLE Tx, Rx
	//USART2->CR1 |= 0x2000;				//ENABLE USART2
	USART2->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
}

int USART_read()
{
	while(!(USART2->SR & USART_SR_RXNE));		//wait until character arrives
	return USART2->DR;
}

int USART2_write(int ch)
{
	//wait while the Tx buffer is empty
	//while(!(USART2->SR & (1U<<7)));  USART_SR_TXE
	while(!(USART2->SR & USART_SR_TXE));  
	USART2->DR = (ch & 0xFF);
	return ch;
}

struct __FILE{int handle;};
FILE __stdin = {0};
FILE __stdout = {1};
FILE __stderr = {2};

int fgetc(FILE *f)
{
	int c;
	c = USART_read();
	if(c == '\r')
	{
		USART2_write(c);
		c = '\n';
	}
	//USART2_write(c);
	
	return c;
}

int fputc(int c,FILE *f)
{
	return USART2_write(c);
}
