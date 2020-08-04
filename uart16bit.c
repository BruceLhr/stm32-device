//USART_RX_STA
//bit15		�������
//bit11		��������λ��־λ
//bit10��	��������λ��־λ
//bit9��	������ձ�־λ
//bit8��	��λ�ݴ��־λ
//bit7~0��	��λ�ݴ�����
const u8 _CommandIndex[_CommandIndex_Max] = {0x02,0x03,0x04,0x0A,0x0B,\
															0x16,0x17,0x18,0x19,0x20,\
															0x21,0x22,0x23,0x24,0x25,\
															0x27,0x33,0xFF};
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	static u32 rxNow=0;
	if(huart->Instance==USART1)//����Ǵ���1
	{

		if((USART_RX_STA&0x8000)==0)//����δ���
		{
			if((USART_RX_STA&0x100)==0)//��λ�ݴ�����
			{
				USART_RX_STA|=(aRxBuffer[0]&0xFF);
				USART_RX_STA|=0x100;
			}
			else
			{
				u16 tempBuffer=0;
				tempBuffer=((USART_RX_STA&0xFF)<<8)+(aRxBuffer[0]&0xFF);
				USART_RX_STA&=0xFEFF;
				if((USART_RX_STA&0x200)==0)//������ձ�־λ
				{
					u8 tempIndex=0;
					for(tempIndex=0;tempIndex<_CommandIndex_Max;tempIndex++)
					{
						if(tempBuffer==_CommandIndex[tempIndex])
						{
							USART_RX_BUF[0]=tempBuffer;
							USART_RX_STA|=0x200;
						}
					}
				}
				else if((USART_RX_STA&0x400)==0)//��������λ��־λ
				{
					USART_RX_BUF[1]=tempBuffer;
					USART_RX_STA|=0x400;
				}
				else if((USART_RX_STA&0x800)==0)//��������λ��־λ
				{
					USART_RX_BUF[2]=tempBuffer;
					rxNow=(USART_RX_BUF[1]<<16)+(USART_RX_BUF[2]);
					USART_RX_STA|=0x800;
				}
				else
				{	
					if(rxNow==0)
						USART_RX_STA|=0x8000;
					else
					{
						USART_RX_BUF[3+((USART_RX_BUF[1]<<16)+(USART_RX_BUF[2]))-rxNow]=tempBuffer;
						rxNow--;
					}
				}
			}
		}
	}
}