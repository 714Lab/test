
#include "system.h"
#include "SysTick.h"
//#include "led.h"
#include "usart.h"
#include "time.h"
#include "dma.h"


#define send_buf_len 2000
u8 send_buf[send_buf_len];
/*******************************************************************************
* 函 数 名         : Send_Data
* 函数功能		   : 要发送的数据
* 输    入         : p：指针变量			 
* 输    出         : 无
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组
	//LED_Init(); 
	UART4_Init(9600);
//	USART1_Init(9600);
	DMAx_Init(DMA1_Channel4,(u32)&USART1->DR,(u32)send_buf,send_buf_len);
	Send_Data(send_buf);
//TIM4_Init(8000,360);//新加代码句  时钟定时20ms
	
	while(1)
	{
			
			USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //使能串口1的DMA发送     
			DMAx_Enable(DMA1_Channel4,send_buf_len);     //开始一次DMA传输！DMA1,channel4
//		  Send_Data(send_buf);
//		if(DMA_GetFlagStatus(DMA1_FLAG_TC4)!=0)//判断通道4传输完成
//				{
//					DMA_ClearFlag(DMA1_FLAG_TC4);
//					break;
//				}
	}
}
