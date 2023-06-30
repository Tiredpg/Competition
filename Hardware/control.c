#include "stm32f10x.h" 
#include "PWM.h"
#include "encoder.h"
#include "Delay.h"
extern int Encoder;
extern int Target;
extern float Rev;
int Encoder1=0;
int moto ,AIN1,AIN2,PWMA;
float n=0;
int Bias=0,Last_bias=0;
int Pwm=0;
extern int X;
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
if(moto<-max) moto=-max;
if(moto>max) moto=max;
}

void Set_Pwm(int moto){
if(moto>0){GPIO_SetBits(GPIOA,GPIO_Pin_4);//PA4为高电平
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);//PA5为低电平，正转
	}
else
{GPIO_SetBits(GPIOA,GPIO_Pin_5);//PA5为高电平
	GPIO_ResetBits(GPIOB,GPIO_Pin_4);//PA4为低电平，反转
	}
	PWMA=myabs(moto);
	PWM1_SetCompare1(PWMA);
}

void TIM3_IRQHandler(void){//也可以放在使用它的main里面

if(TIM_GetITStatus(TIM3,TIM_FLAG_Update)==SET){//获取中断标志位

     Encoder=Encoder_Get();//定时读取CNT
	//Encoder1=Encoder*25;
	Encoder1=Encoder/4;//总脉冲数
	Rev=speed(Encoder1);
	X=Rev*100;
	moto=Incremental_PI(X, Target);
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);//PC13为低电平
	xianfu();
	Set_Pwm(moto);
TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//清除中断标志位
}	
}	
