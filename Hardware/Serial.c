#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>

double RxData=0;
void Serial_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure1;
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_9;//Tx输出
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_AF_PP;//推挽输出，stm32对端口的绝对控制
	GPIO_Init(GPIOA,&GPIO_InitStructure1);//配置端口模式*/
	
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_10;//Rx输入
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IPU;//浮空输入或上拉输入
	GPIO_Init(GPIOA,&GPIO_InitStructure1);//配置端口模式*/
	
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=9600;//波特率
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//硬件流控制,这里不使用
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;// 发送接收，都使用，用或
	USART_InitStructure.USART_Parity=USART_Parity_No;//校验位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;//停止位
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;//字长8位
	USART_Init(USART1, &USART_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
}

void Serial_SendByte(uint8_t Byte){//发送数据函数
	
	USART_SendData(USART1,Byte);//Byte写入TDR
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//等待TDR转入移位寄存器,FlagStatus不需要手动清除
	
}

void Serial_SendArray(uint8_t *Array,uint16_t Length){//发送一个数组

uint16_t i;
for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)
{//发送一个字符串
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{//求X的Y次方
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number, uint8_t Length)
{//发送一个数字
	uint8_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');//字符0是偏移
	}
}

//int fputc(int ch, FILE *f)
//{//fputc重定向到串口，print输出到串口
//	Serial_SendByte(ch);
//	return ch;
//}
void Serial_Printf(char *format, ...)
	{//print先输出到string数组，再将数组打印到串口，不涉及重定向
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}

double Get_ReceiveData(void){

if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET){//如果接受到数据进入if
RxData=USART_ReceiveData(USART1);//获取接收数据寄存器的值，读取后自动清除标志位
}
return RxData;
}

