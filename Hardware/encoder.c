#include "stm32f10x.h" 
void Encoder_Init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//开启时钟4，时钟1输出PWM
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//端口配置 PB3
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB
	
	
	TIM_InternalClockConfig(TIM4);//选择内部时钟驱动时基单元，不写也有默认

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//1分频，不分频，滤波器的采样频率
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up ;//向上计数
	TIM_TimeBaseInitStructure.TIM_Period=65536-1;//自动重装器，越大计数越多,ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler=1-1;//预分频器，越小频率越高,PSC,1KHZ
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//高级计时器才用
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//时基单元初始化，更新中断和更新事件同时发生
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);//手动清除中断标志位，避免刚初始化就进中断

	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(& TIM_ICInitStructure);//结构体赋默认值
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 ;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;//配置滤波器，其采样频率不改变信号频率
	TIM_ICInitStructure.TIM_ICSelection= TIM_ICPolarity_BothEdge;//上升沿下降沿有效
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//高低电平极性翻转
	TIM_ICInit(TIM4, &TIM_ICInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2 ;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;//配置滤波器，其采样频率不改变信号频率
	TIM_ICInitStructure.TIM_ICSelection= TIM_ICPolarity_BothEdge;//上升沿下降沿有效
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//高低电平极性翻转
	TIM_ICInit(TIM4, &TIM_ICInitStructure);

    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,
     	 TIM_ICPolarity_Falling, TIM_ICPolarity_Rising);//配置编码器接口的函数,覆盖前面配好的2个通道的极性
		 
		  
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
  //Reset counter
  TIM_SetCounter(TIM4,0);
  TIM_Cmd(TIM4, ENABLE); 
}

uint16_t Encoder_Get(void){
uint16_t Encoder_TIM;
Encoder_TIM=TIM_GetCounter(TIM4);
TIM_SetCounter(TIM4, 0);
return Encoder_TIM;
}


//int Read_Encoder(uint8_t TIMX){
//int Encoder_TIM;
//	switch(TIMX){
//		case2:Encoder_TIM=(short)TIM2->CNT;TIM2->CNT=0;break;
//	    case3:Encoder_TIM=(short)TIM3->CNT;TIM3->CNT=0;break;
//		case4:Encoder_TIM=(short)TIM4->CNT;TIM4->CNT=0;break;
//		default:Encoder_TIM=0;
//	}
//return Encoder_TIM;//取计数器的值进行PID调试
//}


void TIM4_IRQHandler(void){
if(TIM_GetITStatus(TIM4,TIM_FLAG_Update)==SET){//获取中断标志位

TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//清除中断标志位
}	

}

