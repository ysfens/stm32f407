#include "stm32f4xx.h"                  // Device header
#include <stdio.h>
#include <stdlib.h>

char str[50];
uint32_t i;

void delay(uint32_t time)						// delay configuration
{while(time)
	time--;
}
void USART_Puts(USART_TypeDef* USARTx, volatile char *s)		//when we want to get a data we must to use this configuration
{
	while(*s)
	{
		while(!(USARTx ->SR & 0x00000040 ));
		USART_SendData(USARTx, *s);
		*s++;
	}
}
int main()
{
  GPIO_InitTypeDef	GPIO_InitStructure;					//structure configurations
	USART_InitTypeDef USART_InitStructure;
	
	//clock configurations
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);			
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//structure configurations
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	
	//usart configurations
	USART_InitStructure.USART_BaudRate            = 115200;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Tx;
	USART_InitStructure.USART_Parity              = USART_Parity_No;
	USART_InitStructure.USART_StopBits						= USART_StopBits_1;
	USART_InitStructure.USART_WordLength					= USART_WordLength_8b;
	USART_Init(USART2,&USART_InitStructure);
	USART_Cmd(USART2, ENABLE);
	
	while(1)
	{

		sprintf(str,"UGUR BABBAAAA\n");
		USART_Puts(USART2,str);
		delay(16800000);
	}
	
}


