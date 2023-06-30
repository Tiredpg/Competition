#include "stm32f10x.h" 
#include "Serial2.h"	  
// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
uint8_t receive;
 void Serial2_init( uint32_t bound )//bound为9600波特率
{
	/* GPIO端口设置 */
	GPIO_InitTypeDef	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStructure;
 
 
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE ); 
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE );         /* 使能USART2，GPIOA时钟 */
 
	/* PA2 TXD2 */
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_Init( GPIOA, &GPIO_InitStructure );
 
	/* PA3 RXD2 */
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN_FLOATING;
	GPIO_Init( GPIOA, &GPIO_InitStructure );
 
 
	/* USART 初始化设置 */
	USART_InitStructure.USART_BaudRate		= bound;                                /* 串口波特率 */
	USART_InitStructure.USART_WordLength		= USART_WordLength_8b;                  /* 字长为8位数据格式 */
	USART_InitStructure.USART_StopBits		= USART_StopBits_1;                     /* 一个停止位 */
	USART_InitStructure.USART_Parity		= USART_Parity_No;                      /* 无奇偶校验位 */
	USART_InitStructure.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;       /* 无硬件数据流控制 */
	USART_InitStructure.USART_Mode			= USART_Mode_Rx | USART_Mode_Tx;        /* 收发模式 */
 
	USART_Init( USART2, &USART_InitStructure );                                             /* 初始化串口1 */
	USART_Cmd( USART2, ENABLE );                                                            /* 使能串口 2 */
	
	
	//Usart1 NVIC 配置
	NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
}
void USART2_IRQHandler(void) {//串口2中断

	if(USART_GetFlagStatus(USART2,USART_FLAG_RXNE)==1)     
		{
			receive=USART_ReceiveData(USART2); 
			
			if(receive == 0x41)       // PC13输出低电平，点亮LED      
			{
				GPIO_ResetBits(GPIOC,GPIO_Pin_13);				
			}
			if(receive == 0x42)       // PC13输出低电平，点亮LED      
			{
				GPIO_SetBits(GPIOC,GPIO_Pin_13);				
			}
		}


}

	


