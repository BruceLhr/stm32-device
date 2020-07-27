//independent watch dog
void IWDG_Init(u8 prer,u16 rlr) //4,625		1s		Tout=((4*2^prer)*rlr)/40 (ms)
{	
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  
	
	IWDG_SetPrescaler(prer);  
	
	IWDG_SetReload(rlr);  
	
	IWDG_ReloadCounter();  
	
	IWDG_Enable();  
}

void IWDG_Feed(void)
{   
 	IWDG_ReloadCounter();//reload										   
}

//window watch dog
void WWDG_Init(u8 tr,u8 wr,u32 fprer)//0X7F,0X5F,WWDG_Prescaler_8		Fwwdg=PCLK1/(4096*2^fprer). 
{ 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE); 

	WWDG_CNT=tr&0x7f; 
	WWDG_SetPrescaler(fprer);

	WWDG_SetWindowValue(wr);

	WWDG_Enable(WWDG_CNT);	

	WWDG_ClearFlag();

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; 
	NVIC_Init(&NVIC_InitStructure);

	WWDG_EnableIT();
} 
void WWDG_IRQHandler(void)
	{

	WWDG_SetCounter(WWDG_CNT);	  //当禁掉此句后,窗口看门狗将产生复位

	WWDG_ClearFlag();	  //清除提前唤醒中断标志位

	}