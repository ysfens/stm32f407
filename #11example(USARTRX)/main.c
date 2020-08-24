#include "stm32f4xx.h"                  // Device header
#include <stdio.h>
#include <stdlib.h>

int i=0;
char str[50];
char receive;

void delay(uint32_t time)
{
	time=time*16800;
	while(time)
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

char USARTReceive(void)
{
char re=0;
    //
    // Loop while there are more characters to send.
    //

        re=USART_ReceiveData(USART3);// Last Version USART_SendData(USART1,(uint16_t) *pucBuffer++);
        /* Loop until the end of transmission */
        while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
				
return re;
}


int main()
	
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,  ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,  ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,  ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	//TRANCEIVER
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//RECEIVER
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
	
	
	
	
	USART_InitStructure.USART_BaudRate					  = 115200;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	
	USART_InitStructure.USART_Mode								= USART_Mode_Tx ;
	USART_InitStructure.USART_Parity							= USART_Parity_No;
	USART_InitStructure.USART_StopBits						= USART_StopBits_1;
	USART_InitStructure.USART_WordLength 					=	USART_WordLength_8b;
	USART_Init(USART2, &USART_InitStructure);
	USART_Cmd(USART2, ENABLE);
	

	USART_InitStructure.USART_BaudRate					  = 115200;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	
	USART_InitStructure.USART_Mode								= USART_Mode_Rx ;
	USART_InitStructure.USART_Parity							= USART_Parity_No;
	USART_InitStructure.USART_StopBits						= USART_StopBits_1;
	USART_InitStructure.USART_WordLength 					=	USART_WordLength_8b;
	USART_Init(USART3, &USART_InitStructure);
	USART_Cmd(USART3, ENABLE);
	

	while(1)
		
	{
		while(1)
		{
		
		receive = USARTReceive();
		
	if(receive == '1')
	{
			
		sprintf(str,"A");
		USART_Puts(USART2,str);
	  delay(500);
		break;
	}
	
}
		
	
	}
}


