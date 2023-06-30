#include "stm32f10x.h" 
#include "control.h"
//extern uint16_t Num;//跨文件使用变量
void Timer_Init(int arr,int psc){//初始化TIM3，通用定时器,TIM3是APB1总线外设
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//开启时钟
	
	TIM_InternalClockConfig(TIM3);//选择内部时钟驱动时基单元，不写也有默认
//	TIM_ETRClockMode2Config(TIM3, TIM_ExtTRGPSC_OFF, 
// TIM_ExtTRGPolarity_NonInverted,0x00);//选择ETR通过外部时钟模式2输入的时钟，第二个为外部触发预分频器
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//1分频，不分频，滤波器的采样频率
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up ;//向上计数
	TIM_TimeBaseInitStructure.TIM_Period=arr;//自动重装器，越大计数越多
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;//预分频器，越小频率越高，两个值定时1s
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//高级计时器才用
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//时基单元初始化，更新中断和更新事件同时发生
	//TIM_ClearFlag(TIM3, TIM_FLAG_Update);//手动清除中断标志位，避免刚初始化就进中断
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//使能中断输出，打通到NVIC，第二个参数更新中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//先选择分组方式，每个模块相同，或者放在主函数开始
    NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;//指定中断通道开启或关闭
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//中断通道使能，失能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM3, ENABLE);//使能计数器，运行控制
}

//void TIM3_IRQHandler(void){//中断函数也可以放在使用它的main里面

//if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET){//获取中断标志位

//       Num++;
//	
//TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除中断标志位
//}
//	
//}
