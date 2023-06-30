#include "stm32f10x.h" 
void PWM1_Init(uint16_t arr,uint16_t psc){//3路电机PWM输出，共用一个定时器TIM2，频率周期（可自定义）一致，每路PWM占空比各自可调

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);//端口重映射,部分重映射方式1
	//GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);//也可以用来解除调试端口复用
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出，输出数据寄存器控制GPIO，这里需要定时器来控制要用复用输出模式
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	TIM_InternalClockConfig(TIM1);//选择内部时钟驱动时基单元，不写也有默认
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//1分频，不分频，滤波器的采样频率
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up ;//向上计数
	TIM_TimeBaseInitStructure.TIM_Period=arr;//自动重装器，越大计数越多,ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;//预分频器，越小频率越高,PSC,1KHZ
	//TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//高级计时器才用
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);//时基单元初始化，更新中断和更新事件同时发生
	//TIM_ClearFlag(TIM1, TIM_FLAG_Update);//手动清除中断标志位，避免刚初始化就进中断
	
	
	TIM_OCInitTypeDef TIM_OCInitStructure1;
	TIM_OCStructInit(&TIM_OCInitStructure1);//可以先给结构体变量整体赋初始值，再更改具体需要的值
	TIM_OCInitStructure1.TIM_OCMode = TIM_OCMode_PWM1;//输出比较模式
	TIM_OCInitStructure1.TIM_OCPolarity=TIM_OCPolarity_High ;//极性,高极性，极性不反转，REF直接输出
	TIM_OCInitStructure1.TIM_OutputState = TIM_OutputState_Enable ;//输出比较使能
	TIM_OCInitStructure1.TIM_Pulse=0; //设置CCR
	TIM_OC1Init(TIM1, &TIM_OCInitStructure1);//输出比较单元配置
	
	TIM_OCInitTypeDef TIM_OCInitStructure2;
	TIM_OCStructInit(&TIM_OCInitStructure2);//可以先给结构体变量整体赋初始值，再更改具体需要的值
	TIM_OCInitStructure2.TIM_OCMode = TIM_OCMode_PWM1;//输出比较模式
	TIM_OCInitStructure2.TIM_OCPolarity=TIM_OCPolarity_High ;//极性,高极性，极性不反转，REF直接输出
	TIM_OCInitStructure2.TIM_OutputState = TIM_OutputState_Enable ;//输出比较使能
	TIM_OCInitStructure2.TIM_Pulse=0; //设置CCR
    TIM_OC2Init(TIM1, &TIM_OCInitStructure2);//输出比较单元配置,两个通道用一个计数器，频率一样，占空比各自设定，相位同步
//	
	TIM_OCInitTypeDef TIM_OCInitStructure3;
	TIM_OCStructInit(&TIM_OCInitStructure3);//可以先给结构体变量整体赋初始值，再更改具体需要的值
	TIM_OCInitStructure3.TIM_OCMode = TIM_OCMode_PWM1;//输出比较模式
	TIM_OCInitStructure3.TIM_OCPolarity=TIM_OCPolarity_High ;//极性,高极性，极性不反转，REF直接输出
	TIM_OCInitStructure3.TIM_OutputState = TIM_OutputState_Enable ;//输出比较使能
	TIM_OCInitStructure3.TIM_Pulse=0; //设置CCR
	TIM_OC3Init(TIM1, &TIM_OCInitStructure3);
	
    TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable); //CH1使能预装载寄存器
    TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable); //CH2使能预装载寄存器
    TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable); //CH2使能预装载寄存器
    TIM_CtrlPWMOutputs(TIM1,ENABLE);//高级定时器输出必须
    TIM_ARRPreloadConfig(TIM1,ENABLE);//TIM1在ARR上的预装寄存器
    TIM_Cmd(TIM1, ENABLE);//使能计数器，运行控制
	

}

void PWM1_SetCompare1(uint16_t Compare1){
	
TIM_SetCompare1(TIM1, Compare1);//单独更改通道1CCR值

}

void PWM1_SetCompare2(uint16_t Compare2){
	
TIM_SetCompare2(TIM1, Compare2);//单独更改通道2CCR值

}

void PWM1_SetCompare3(uint16_t Compare3){
	
TIM_SetCompare3(TIM1, Compare3);//单独更改通道3CCR值

}

void PWM1_SetPrescaler(uint16_t Prescaler){//调用此函数通过PSC改变PWM频率，不改变占空比，上面3个改占空比

 TIM_PrescalerConfig(TIM1,  Prescaler,  TIM_PSCReloadMode_Update );
}



