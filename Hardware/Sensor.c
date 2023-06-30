#include "stm32f10x.h" 
void Sensor_GpioInit(void){

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//第一个参数可以按位或，配置多个时钟
	GPIO_InitTypeDef GPIO_InitStructure1;
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;//按位或多个管脚，all选择全部管脚
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
	GPIO_Init(GPIOE,&GPIO_InitStructure1);//配置端口模式*/
	GPIO_SetBits(GPIOE,GPIO_Pin_5);//输出高电平，关灯
	GPIO_SetBits(GPIOE,GPIO_Pin_9);//输出高电平，关蜂鸣器
	GPIO_ResetBits(GPIOE,GPIO_Pin_9);//输出低电平，关激光笔
	
}