#include "stm32f10x.h" 

uint16_t count=0;
void CountSensor_Init(void){//初始化
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//配置AFIO。EXTI,NVIC不需要开启时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//EXTI配置上，下拉输入或浮空输入
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);//AFIO外部中断引脚配置完成
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;//中断线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能中断
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//先选择分组方式，每个模块相同，或者放在主函数开始
    NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn ;//指定中断通道开启或关闭
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//中断通道使能，失能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
}

uint16_t Count_GetNum(void){
	
return count;
	
}


void EXTI15_10_IRQHandler(void){//中断函数不用声明

if(EXTI_GetITStatus(EXTI_Line14)==SET){//先判断是不是EXTI14进入

	count++;
	
EXTI_ClearITPendingBit(EXTI_Line14);//执行完后清除中断标志位
}

}


