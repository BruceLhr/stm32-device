NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

void EXTIX_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
   	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
    
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	GPIO_Init(GPIOE, &GPIO_InitStructure);

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	

  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;				
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		
  	NVIC_Init(&NVIC_InitStructure);
}


void EXTI3_IRQHandler(void)
{
	u16 delayt;
	for(delayt=0;delayt<2000;delayt++);
	if(KEY1==0)
	{				 

	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);
}