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

uint8_t i;
uint16_t Num=0;//跨文件使用变量
int Target=100;//设定目标转数/s
uint16_t Encoder=0;
float Rev,test1,test2=0;
int X=0;//放大作用
uint16_t ADValue;
extern int Encoder1;
extern int Pwm;
extern int moto;
float Voltage;
int E=6;
uint8_t DataA[]={0x01,0x02,0x03,0x04};
uint8_t DataB[]={0,0,0,0};
double Length;//超声波测距

int main(void){

	
	PWM1_Init(7199,0);
		while(1){ 	
		PWM1_SetCompare1(7200);
		}
		123
	}
		  

  

