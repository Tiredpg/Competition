#include "stm32f10x.h" 
#include   "Delay.h"// Device header
#include   "Key.h"
#include   "LED.h"
#include   "Buzzer.h"
#include   "Light.h"
#include   "OLED.h"
#include   "CountSensor.h"
#include   "Timer.h"
#include   "PWM.h"
#include   "Servo.h"
#include    "Motor.h"
#include    "IC.h"
#include    "control.h"
#include    "encoder.h"
#include    "Usart.h"
#include    "AD.h"
#include    "MyDMA.h"
#include    "Serial.h"
#include    "Matrix.h"
#include    "hcsr04.h"
#include    "Serial2.h"
#include    "Sensor.h"
uint8_t i;
uint16_t Num=0;//跨文件使用变量
int Target=100;//设定目标转数/s
uint16_t Encoder=0;
uint16_t Encoder1=0;
float Rev4,Rev3,test1,test2=0;
int X4=0;//放大作用
int X3=0;//放大作用
double ADValue;
extern int Encoder4;
extern int Encoder3;
extern int Pwm;
extern int moto4;
extern int moto3;
float Voltage;
int E=6;
uint8_t DataA[]={0x01,0x02,0x03,0x04};
uint8_t DataB[]={0,0,0,0};
double Length;//超声波测距
double capture;

int SEARCH_L2_IO;
int SEARCH_L1_IO;
int SEARCH_M_IO;
int SEARCH_R1_IO;
int SEARCH_R2_IO;
int item1=0;//停止次数
int item2=0;//
uint16_t AD1,AD2,AD3,AD4,AD5,AD6,AD7;

int main(void){

	   // AD_Init();
		Sensor_GpioInit();//激光笔，蜂鸣器，LED,灰度传感器端口初始化

		//OLED_Init();
		
	    Motor_Init();//电机逻辑口 pA4,5;PC1,2为电机逻辑口；PA
	    //Encoder_Init();
	    PWM1_Init(7199,49);//ARR+1=510,PSC+1=7200,PWM频率为100hz

	while(1){ 	
			
		
		SEARCH_L2_IO=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14);
		SEARCH_L1_IO=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_13);
		SEARCH_M_IO=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12);
		SEARCH_R1_IO=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11);
		SEARCH_R2_IO=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10);
	   //AD1=AD_GetValue(ADC_Channel_1);
	   //AD2=AD_GetValue(ADC_Channel_2);
	   //AD3=AD_GetValue(ADC_Channel_3);
	   //AD4=AD_GetValue(ADC_Channel_4);
	   //AD5=AD_GetValue(ADC_Channel_5);
	   //AD6=AD_GetValue(ADC_Channel_6);
	   //AD7=AD_GetValue(ADC_Channel_7);
		if(SEARCH_L2_IO==0&&SEARCH_L1_IO==0&&SEARCH_M_IO==1&&SEARCH_R1_IO==0&&SEARCH_R2_IO==0)//中间都检测到直行
		{
			PWM1_SetCompare1(3800);
			PWM1_SetCompare2(2600);
		}
				
		if(SEARCH_L1_IO==1)//L1检测到，左转
		{
			PWM1_SetCompare1(0);
			PWM1_SetCompare2(1000);
			Delay_ms(100);
		}

		if(SEARCH_R1_IO==1)//R1检测到，右转
		{
			PWM1_SetCompare1(1000);
			PWM1_SetCompare2(0);
			Delay_ms(100);
		}
		if(SEARCH_L2_IO==1&&SEARCH_L1_IO==1&&SEARCH_M_IO==1&&SEARCH_R1_IO==1&&SEARCH_R2_IO==1)
		{
			PWM1_SetCompare1(0);
			PWM1_SetCompare2(0);
		}
		
	}
	
}
		  

  

