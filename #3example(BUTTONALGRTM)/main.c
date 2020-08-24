#include "stm32f4xx.h"                  // Device header

int main()
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	uint8_t button;
	uint8_t buffer=0;
	
	//clock congiguration
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	
	//led configuration
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	//button configuration
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	while(1)
	{
		button = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
		while( GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
		buffer=buffer+button;
		
		if(buffer%2)
		{
			GPIO_SetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_14);
			GPIO_ResetBits(GPIOD,GPIO_Pin_13|GPIO_Pin_15);
		}
		else 
		{
			GPIO_SetBits(GPIOD,GPIO_Pin_13|GPIO_Pin_15);
			GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_14);
		}
	/*	else
		{
			GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
		}*/
	}
	
	
}

