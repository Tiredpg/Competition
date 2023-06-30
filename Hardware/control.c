#include "stm32f10x.h" 
#include "PWM.h"
#include "encoder.h"
#include "Delay.h"
extern int Encoder;
extern int Encoder1;
extern int Target;
extern float Rev4;
extern float Rev3;
int Encoder4=0;//TIM4编码器总脉冲数
int Encoder3=0;//TIM5编码器总脉冲数
int moto4,AIN1,AIN2,PWMA,moto3;
float n=0;
int Bias=0,Last_bias=0;
int Pwm=0;
extern int X4;
extern int X3;
float speed(int num)
{
    n=(num/0.01)/390;// n/s
    return n;
}

int Incremental_PI(int X,int Target){//编码电机PI控制

    float Kp=0.01,Ki=1.2;
	Bias= Target-X;//计算误差
	Pwm+=Kp*(Bias- Last_bias)+Ki*Bias;//PI公式
    Last_bias=Bias;//保存上一次误差
	if(Pwm<-7100) Pwm=-7100;
    if(Pwm>7100) Pwm=7100;
	return Pwm;
}

int myabs(int a){//取绝对值
 int temp;
 if(a<0) temp = -a;
 else  temp = a;
 return temp;
}

void xianfu(void){//限幅
int max=7100;
if(moto4<-max) moto4=-max;
if(moto4>max) moto4=max;
if(moto3<-max) moto3=-max;
if(moto3>max) moto3=max;
}

void Set_Pwm(int moto4,int moto3){
if(moto4>0&&moto3>0){GPIO_SetBits(GPIOA,GPIO_Pin_4);//PA4为高电平
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);//PA5为低电平，正转
	GPIO_SetBits(GPIOC,GPIO_Pin_1);//PA6为高电平
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);//PA7为低电平，正转
	}
else
{
	GPIO_SetBits(GPIOA,GPIO_Pin_5);//PA5为高电平
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);//PA4为低电平，反转
	GPIO_SetBits(GPIOC,GPIO_Pin_2);//PC2为高电平
	GPIO_ResetBits(GPIOC,GPIO_Pin_1);//PC1为低电平，反转
	}
	PWMA=myabs(moto4);
	PWM1_SetCompare1(PWMA);//PA8
	PWMA=myabs(moto3);
	PWM1_SetCompare2(PWMA);//PA9
}

void TIM5_IRQHandler(void){//也可以放在使用它的main里面

if(TIM_GetITStatus(TIM5,TIM_FLAG_Update)==SET){//获取中断标志位

     Encoder=Encoder_GetTIM4();//定时读取CNT
	Encoder1=Encoder_GetTIM3();
	Encoder4=Encoder/4;//4的总脉冲数
	Encoder3=Encoder1/4;//3的总脉冲数
	Rev4=speed(Encoder4);
	X4=Rev4*100;
	Rev3=speed(Encoder3);
	X3=Rev3*100;
	moto4=Incremental_PI(X4, Target);
	moto3=Incremental_PI(X3, Target);
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);//PC13为低电平
	xianfu();
	Set_Pwm(moto4,moto3);
TIM_ClearITPendingBit(TIM5,TIM_IT_Update);//清除中断标志位
}	
}	
