void pwm_output_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = 1000;     
  TIM_TimeBaseStructure.TIM_Prescaler = 71; 
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         //预分频系数
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数方式
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;               
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);    

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC1
	
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM4, ENABLE);
}

void set_compare_value(uint16_t value)
{
	TIM_SetCompare1(TIM4, value);
}

