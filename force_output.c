void force_output_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;               
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);   
  
  TIM_TimeBaseStructure.TIM_Period = 1000;     
  TIM_TimeBaseStructure.TIM_Prescaler = 71; 
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         //预分频系数
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数方式
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
  
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_Cmd(TIM4, ENABLE);
	
	TIM4->CCMR1 |= 1 << 11;		//ch2 preload en
	TIM4->CCMR1 |= 5 << 12;		//force valid
	TIM4->CCER &= ~(1 << 5);	//high is valid
	TIM4->CCER |= 1 << 4;		//out en
}

