#include "stm32f4xx.h"                  // STM32F407	LED Yakma Uygulamasi

int main()
	
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOD,GPIO_Pin_12);
	GPIO_SetBits(GPIOD,GPIO_Pin_13);
  GPIO_SetBits(GPIOD,GPIO_Pin_14);
	GPIO_SetBits(GPIOD,GPIO_Pin_15);
	
	
	}	
	
