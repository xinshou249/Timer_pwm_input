void pwm_input_init(void)
{	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	TIM_ICInitTypeDef   TIM_ICInitStruct;
	NVIC_InitTypeDef    NVIC_InitStructe;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;               
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;            
  GPIO_Init(GPIOA, &GPIO_InitStructure);     
	
	TIM_TimeBaseStructure.TIM_Period = 10000;     
  TIM_TimeBaseStructure.TIM_Prescaler = 71; 
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         //预分频系数
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数方式
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
	NVIC_InitStructe.NVIC_IRQChannel = TIM2_IRQn;                     
	NVIC_InitStructe.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructe.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructe.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructe);  
	 
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;        //选择通道
	TIM_ICInitStruct.TIM_ICFilter=0x0;                            //滤波系数
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;//触发模式    
	TIM_ICInitStruct.TIM_ICPrescaler=TIM_CKD_DIV1;    //预分频选择
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;//端口映射
	TIM_PWMIConfig(TIM2,&TIM_ICInitStruct);
	
	TIM_SelectInputTrigger(TIM2, TIM_TS_TI1FP1); 
	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);  //配置为主从复位模式
	TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable); 
	TIM_ITConfig(TIM2, TIM_IT_CC1|TIM_IT_Update, ENABLE);          //中断配置
	
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
  TIM_Cmd(TIM2, ENABLE); 	
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)//定时器中断清零
  {
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
  }
	else if(TIM_GetITStatus(TIM2,TIM_IT_CC2)!=RESET)//通道1触发清零
  {
        TIM_ClearITPendingBit(TIM2,TIM_IT_CC2);
  }
	else if(TIM_GetITStatus(TIM2,TIM_IT_CC1)!=RESET)//通道2触发清零
  {
		print("TIM2 CYCLE=%d , HIGH PULSE WIDTH=%d \r\n",TIM_GetCapture1(TIM2),TIM_GetCapture2(TIM2));  //my print function                      
		TIM_ClearITPendingBit(TIM2,TIM_IT_CC1);
	}
}
