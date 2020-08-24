#include "stm32f4xx.h"                  // Device header

void delay(uint32_t time)
{
	while(time)
		time--;
	
}



void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
		//user code
		GPIO_SetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
		delay(2680000);
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
		delay(2680000);
		//user code
	}
}

int main()
	
{
	GPIO_InitTypeDef  			 GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;
	
	// CLOCK CONFIGURATION
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,  ENABLE);
	
	// LED CONFIGURATION
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	// TIMER OPTIONS CONFIGURATION
	TIM_TimeBaseStructure.TIM_ClockDivision 		= TIM_CKD_DIV4;
	TIM_TimeBaseStructure.TIM_CounterMode   		= TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period  					= 20;
	TIM_TimeBaseStructure.TIM_Prescaler					= 4199;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 50;		//MOST IMPORTANT (the overflow quantity)
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel 						       = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd 							 = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x01;
	NVIC_Init(&NVIC_InitStructure);

}



