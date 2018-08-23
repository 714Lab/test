#include "time.h"
#include "led.h"
#include "usart.h"
#include "dma.h"


//#define send_buf_len 2000
//u8 send_buf[send_buf_len];
///*******************************************************************************
//* �� �� ��         : Send_Data
//* ��������		   : Ҫ���͵�����
//* ��    ��         : p��ָ�����			 
//* ��    ��         : ��
//*******************************************************************************/
//u8 a;
//void Send_Data(u8 *p)
//{
//	
//	u16 i;
//	a=0xAA;
//	for(i=0;i<send_buf_len;i++)
//	{
//		*p=a;
//		p++;
//	}
//}

/*******************************************************************************
* �� �� ��         : TIM4_Init
* ��������		   : TIM4��ʼ������
* ��    ��         : per:��װ��ֵ
					 psc:��Ƶϵ��
* ��    ��         : ��
*******************************************************************************/
//u16 r ;
//u16 b;
//u8 t=0xAA;
//int flag;
//	r=0xAA;
void TIM4_Init(u16 per,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//ʹ��TIM4ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period=per;   //�Զ�װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //��Ƶϵ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //������ʱ���ж�
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;//��ʱ���ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	
	
	TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ��	
}

/*******************************************************************************
* �� �� ��         : TIM4_IRQHandler
* ��������		   : TIM4�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void TIM4_IRQHandler(void)
{

	//while(1)
	//{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update))
	{
//		  DMAx_Init(DMA1_Channel4,(u32)&USART1->DR,(u32)send_buf,send_buf_len);
//			USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //ʹ�ܴ���1��DMA����     
//			DMAx_Enable(DMA1_Channel4,send_buf_len);     //��ʼһ��DMA���䣡DMA1,channel4
//		  Send_Data(send_buf);
//		USART_SendData(USART1,0xAA);
		
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
//		USART_SendData(USART1,t);
//		while(USART_GetFlagStatus(UART4,USART_FLAG_TC) != SET);
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);	
		
	//}
}


