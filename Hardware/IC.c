#include "stm32f10x.h" 
void IC_Init(void){//输入捕获初始化
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//开启时钟2，时钟1输出PWM
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	TIM_InternalClockConfig(TIM2);//选择内部时钟驱动时基单元，不写也有默认

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//1分频，不分频，滤波器的采样频率
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up ;//向上计数
	TIM_TimeBaseInitStructure.TIM_Period=65536-1;//自动重装器，越大计数越多,ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler=72-1;//预分频器，越小频率越高,PSC,1KHZ
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//高级计时器才用
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//时基单元初始化，更新中断和更新事件同时发生
	//TIM_ClearFlag(TIM2, TIM_FLAG_Update);//手动清除中断标志位，避免刚初始化就进中断
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 ;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;//配置滤波器，其采样频率不改变信号频率
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//分频器改变信号频率
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//直连，交叉通道
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	TIM_PWMIConfig(TIM2,&TIM_ICInitStructure );//PWMI模式,2通道测一个gpio，函数里面，通道2，交叉，下降沿，不能通道3和4
	 TIM_SelectInputTrigger(TIM2, TIM_TS_TI1FP1);//选择从模式输入触发源TRGI
	 TIM_SelectSlaveMode(TIM2,TIM_SlaveMode_Reset);//选择从模式
	 
	 TIM_Cmd(TIM2, ENABLE);//使能计数器，运行控制
}

uint32_t IC_GetFreq(void){
	
	return 1000000/TIM_GetCapture1(TIM2);//读取CCR1的值N，fc为1000000

}

uint32_t IC_GetDuty(void){

return TIM_GetCapture2(TIM2)*100/TIM_GetCapture1(TIM2);//CCR2/CCR1,占空比，xx%	
}


	