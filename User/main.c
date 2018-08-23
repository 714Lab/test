
#include "system.h"
#include "SysTick.h"
//#include "led.h"
#include "usart.h"
#include "time.h"
#include "dma.h"


#define send_buf_len 2000
u8 send_buf[send_buf_len];
/*******************************************************************************
* �� �� ��         : Send_Data
* ��������		   : Ҫ���͵�����
* ��    ��         : p��ָ�����			 
* ��    ��         : ��
*******************************************************************************/
u8 a;
void Send_Data(u8 *p)
{
	
	u16 i;
	a=0xAA;
	for(i=0;i<send_buf_len;i++)
	{
		*p=a;
		p++;
	}
}

int main()
{
//  u8 t=0xAA;
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
	//LED_Init(); 
	UART4_Init(9600);
//	USART1_Init(9600);
	DMAx_Init(DMA1_Channel4,(u32)&USART1->DR,(u32)send_buf,send_buf_len);
	Send_Data(send_buf);
//TIM4_Init(8000,360);//�¼Ӵ����  ʱ�Ӷ�ʱ20ms
	
	while(1)
	{
			
			USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //ʹ�ܴ���1��DMA����     
			DMAx_Enable(DMA1_Channel4,send_buf_len);     //��ʼһ��DMA���䣡DMA1,channel4
//		  Send_Data(send_buf);
//		if(DMA_GetFlagStatus(DMA1_FLAG_TC4)!=0)//�ж�ͨ��4�������
//				{
//					DMA_ClearFlag(DMA1_FLAG_TC4);
//					break;
//				}
	}
}
