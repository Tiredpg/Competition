#include "stm32f10x.h"
#include   "Delay.h"
void Key_Init(void){//按键GPIO初始化
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//按键配置上拉输入
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
}

uint8_t Key_GetNum(void){//返回按键键码
    
	uint8_t KeyNum = 0;
	//GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1);//读取一个引脚输出数据寄存器
	//GPIO_ReadInputData(GPIOB);//读取全部输出数据寄存器
	
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0){//等于零代表按键按下
	 Delay_ms(20);//延时消抖
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0);//按键一直按下卡在这里
	Delay_ms(20);//延时消抖
		KeyNum = 1;//键码
	}
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0){//等于零代表按键按下
	 Delay_ms(20);//延时消抖
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0);//按键一直按下卡在这里
	Delay_ms(20);//延时消抖
		KeyNum = 2;//键码
	}
	 return KeyNum;
}
