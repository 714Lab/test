#include "usart.h"		 
#include "time.h"
#include "dma.h"
/*******************************************************************************
* 函 数 名         : USART1_Init
* 函数功能		   : USART1初始化函数
* 输    入         : bound:波特率
* 输    出         : 无
*******************************************************************************/ 
u16 r;//定义上位机发送数据变量 

//r=0xAA;
u32 b;//定义重装载值过程变量
//int n=1;//16进制权重
//float m=0;
void UART4_Init(u32 bound)
{
   //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
 
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10 ;//TX			   //串口输出PC10
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
	GPIO_Init(GPIOC,&GPIO_InitStructure);  /* 初始化串口输入IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//RX			 //串口输入PC11
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //模拟输入
	GPIO_Init(GPIOC,&GPIO_InitStructure); /* 初始化GPIO */
	

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(UART4, &USART_InitStructure);   
	USART_Cmd(UART4, ENABLE);  //使能串口1 
	
	USART_ClearFlag(UART4, USART_FLAG_TC);
		
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、	
}

/*******************************************************************************
* 函 数 名         : USART1_IRQHandler
* 函数功能		   : USART1中断函数
* 输    入         : 无
* 输    出         : 无
////*******************************************************************************/ 
void UART4_IRQHandler(void)                	//串口4中断服务程序
{
	
//	while(1)
//		{
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //接收中断
	{
		r =USART_ReceiveData(UART4);//(USART1->DR);	//读取接收到的数据
		USART_SendData(UART4,r);
		while(USART_GetFlagStatus(UART4,USART_FLAG_TC) != SET);
//		while(r != 0)
//			{
//			m += (r%10)*n;  // ???????,?????????
//			r /= 10;   // ??16???????,????????
//			n *= 16;     // ????16
//			}
		
		switch(r)
		{			
			case 0:b=0;break;
			case 1:b=1667;break;//ms,    //为什么1000时不起作用？    0.0171r/s , 1r/min
			case 2:b=10000;break;//10ms                              0.1r/s， 6r/min
			case 3:b=20000;break;//20ms                              0.2r/s,  12r/min
			case 4:b=40000;break;//40ms                              0.4r/s,  24r/min
			case 5:b=80000;break;//90ms                              0.5r/s,  48r/min
			case 6:b=100000;break;//180ms                             1r/s  ,  60r/min
			case 7:b=150000;break;       //理论值                     1.5r/s,   90r/min
			case 8:b=166667;break;           //             			    1.5r/s,  100r/min
			case 9:b=200000;break;           //                 			2r/s ,  120r/min
//			case 0x0A:b=10000;break;         //												0.1r/s  6r/min   16进制下用A,B
//			case 0x0B:b=20000;break;         // 			//								2r/s
//			case 0x10:b=200000;break;
		}
//		TIM4_Init(b,360);//4000,360对应20ms 
			USART1_Init(b);
	} 
	USART_ClearFlag(UART4,USART_FLAG_TC);
//		} 	
}



void USART1_Init(u32 bound)
{
   //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
 
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9 ;//TX			   //串口输出PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* 初始化串口输入IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX			 //串口输入PA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //模拟输入
	GPIO_Init(GPIOA,&GPIO_InitStructure); /* 初始化GPIO */
	

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART1, &USART_InitStructure);   
	USART_Cmd(USART1, ENABLE);  //使能串口1 
	
	USART_ClearFlag(USART1, USART_FLAG_TC);
		
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、	
}

/*******************************************************************************
* 函 数 名         : USART1_IRQHandler
* 函数功能		   : USART1中断函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/ 
//void USART1_IRQHandler(void)                	//串口1中断服务程序
//{
//	
//	while(1)
//		{
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
//	{
//		t =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
//		USART_SendData(USART1,t);
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
//	} 
//	USART_ClearFlag(USART1,USART_FLAG_TC);
//		} 	
//}

