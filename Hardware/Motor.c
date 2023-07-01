#include "stm32f10x.h" 
#include "PWM.h"
void Motor_Init(void){
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	//编码电机
	GPIO_InitTypeDef GPIO_InitStructure1;
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure1);
	GPIO_SetBits(GPIOC,GPIO_Pin_6);//PC6为高电平
	GPIO_ResetBits(GPIOC,GPIO_Pin_7);//PC7为低电平，正转
	GPIO_SetBits(GPIOC,GPIO_Pin_1);//PC1为高电平
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);//PC2为低电平，正转
	//PC6和PC7为逻辑输出
	//PC1和PC2为逻辑输出
	
	//步进电机
	GPIO_SetBits(GPIOC,GPIO_Pin_0);//PC0为高电平
	GPIO_SetBits(GPIOC,GPIO_Pin_3);//PC3为高电平
	//PC0为EA
	//PC3控制旋转方向
	
}





