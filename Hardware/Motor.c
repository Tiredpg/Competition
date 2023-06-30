#include "stm32f10x.h" 
#include "PWM.h"
void Motor_Init(void){
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure1;
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure1);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);//PA4为高电平
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);//PA5为低电平，正转
	GPIO_SetBits(GPIOC,GPIO_Pin_1);//PC1为高电平
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);//PC2为低电平，正转
	
	//步进电机
	GPIO_SetBits(GPIOC,GPIO_Pin_0);//PC0为高电平
	GPIO_SetBits(GPIOC,GPIO_Pin_3);//PC3为低电平，正转

	
	//pA4和pA5为逻辑输出
	//pC1和pC2为逻辑输出
	
	
//GPIO_SetBits(GPIOA,GPIO_Pin_4);//PA4为高电平
	//GPIO_ResetBits(GPIOA,GPIO_Pin_5);//PA5为低电平，正转
	//PWM_Init();
}



//void Motor_SetSpeed(int8_t speed){
//if(speed >=0){//此时要正转
//GPIO_SetBits(GPIOA,GPIO_Pin_4);
//GPIO_ResetBits(GPIOA,GPIO_Pin_5);
//PWM1_SetCompare3(speed);
//}
//else{//反转
//GPIO_SetBits(GPIOA,GPIO_Pin_5);
//GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//	PWM1_SetCompare3(-speed);//speed为负数
//}
//}


