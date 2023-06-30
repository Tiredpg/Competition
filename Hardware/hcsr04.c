#include "stm32f10x.h"
#include "hcsr04.h"

extern char value[];    //存储转换后的值
int Val=0;
uint16_t count1=0;//用于时间计数，count是ms数
void hcsr04Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB2PeriphClockCmd(HCSR04_CLK,ENABLE);
	RCC_APB1PeriphClockCmd(HCSR04_TIM_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=HCSR04_TRIG;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;  		//推挽输出
	GPIO_Init(HCSR04_PORT,&GPIO_InitStructure);
	GPIO_ResetBits(HCSR04_PORT, HCSR04_TRIG);    
	
	GPIO_InitStructure.GPIO_Pin=HCSR04_ECHO;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	//浮空输入
	GPIO_Init(HCSR04_PORT, &GPIO_InitStructure);  

	TIM_DeInit(TIM2);
	TIM_TimeBaseStructure.TIM_Period = 999; 
	TIM_TimeBaseStructure.TIM_Prescaler =71; 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //初始化 

	TIM_ClearFlag(TIM2, TIM_FLAG_Update);   //清除更新中断，免得一打开中断立即产生中断
 	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);    //打开定时器更新中断
	TIM_Cmd(TIM2,DISABLE);
}

float UltraSonic_valuetance(void)   //测量超声波距离
{
		float length=0,sum=0;
		int i=0;uint16_t time;
		while(i!=5){		
		GPIO_SetBits(HCSR04_PORT, HCSR04_TRIG);   //拉高电平信号
		Delay_us(20);   //高电平至少10uS
		GPIO_ResetBits(HCSR04_PORT, HCSR04_TRIG); //拉低电平信号    
		/*等待回响信号*/
		while(GPIO_ReadInputDataBit(HCSR04_PORT,HCSR04_ECHO)==0);  //接收到信号ECHO为高电平
		TIM_Cmd(TIM2,ENABLE);        //使能TIM2定时器
		i+=1;				
		while(GPIO_ReadInputDataBit(HCSR04_PORT,HCSR04_ECHO)==1);  //直到回响信号消失
		TIM_Cmd(TIM2,DISABLE);       //失能TIM2定时器
		time=TIM_GetCounter(TIM2);
			length=(time+count1*1000)/58.0;//计算距离t*340/2的变式us/58，计算结果单位为cm
		if(length<=0){//下面进行余震处理
			length=0;
		}
		sum+=length;
		Delay_ms(10);
		TIM_SetCounter(TIM2, 0);//清零计数器的值
		count1=0;//清零用于下一次计数
		}	
		length=sum/5.0;
		return length;
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{
		count1++;//进一次中断说明，计时了1ms
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		
	}
}
