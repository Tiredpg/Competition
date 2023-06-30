#include "stm32f10x.h"
void Light_Init(void){//GPIO B13 初始化函数定义,不写SetBits初始化默认输出低电平
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//光敏传感器配置上拉输入
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_13);//输出高电平
}
uint8_t Light_GetNum(void){
	
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
	
}
