#include "stm32f10x.h"
void LED_Init(void){//LED初始化函数定义,不写SetBits初始化默认输出低电平
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);//输出高电平
}
void LED_ON(void){//打开LED
	
GPIO_ResetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);

}

void LED_OFF(void){//关闭LED
	
GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);

}

void LED_Turn(void){//翻转LED功能 A1
	
if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_0) == 0){//等于零代表按键按下
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1);//PA1为高电平

   } 
else{
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);//PA1为低电平
	
    }
}
