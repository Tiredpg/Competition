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

	    //uart_init(115200);
	
	   // AD_Init();
	
	   //int key_val = 0;
	
	
	  Sensor_GpioInit();//激光笔，蜂鸣器，LED,灰度传感器端口初始化
	//Matrix_ssKey_Pin_Init();
	
	//OLED_Init();
		
		
	    Motor_Init();//电机逻辑口 pA4,5;PC1,2为电机逻辑口；PA
	    //Encoder_Init();
	    PWM1_Init(7199,49);//ARR+1=510,PSC+1=7200,PWM频率为100hz
		//Set_Pwm(1000);
	    //Timer_Init(99,7199);//定时器3，定时10ms中断
	    //OLED_ShowString(1,1,"Target:");
	    //OLED_ShowString(3,1,"Rev:");
      //PWM1_SetCompare1(3600);
      //PWM1_SetCompare2(3600);
	    //Serial_Init();
		//printf("Num=%d\r\n",666);
		//printf("串口初始化成功！\n");
		
		
	    //hcsr04Init();
		//printf("超声波初始化成功！\n");
	
	
	    //Serial2_init(9600);
//        Serial_SendByte('A');
//	    uint8_t MyArray[]={0x42,0x43,0x44,0x45};
//		Serial_SendArray(MyArray,4);
//		Serial_SendString("Hello World!\r\n");//\r\n换行
//		Serial_SendNumber(12345,5);//文本形式12345
//        Serial_Printf("Num=%d\r\n",666);




		while(1){ 	
			
           //Length=UltraSonic_valuetance();
		   //printf("length is:%.3f\n",Length);//注意Length为double
//			capture=TIM_GetCounter(TIM3);
//			printf("capture is:%.3f\n",capture);
			
			//现在输入捕获的代码中的定时器4关了给超声波，在用的时候记得打开
//			key_val = Matrix_Key_Scan();
			
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
if(SEARCH_L2_IO==0&&SEARCH_L1_IO==0&&SEARCH_M_IO==1&&SEARCH_R1_IO==0&&SEARCH_R2_IO==0){//中间都检测到直行


 PWM1_SetCompare1(3600);
 PWM1_SetCompare2(3600);

}
		

if(SEARCH_L1_IO==1){//最左边L2检测到，左转

 PWM1_SetCompare1(0);
 PWM1_SetCompare2(3600);

}

if(SEARCH_R2_IO==1){//最右边R2检测到，右转

 PWM1_SetCompare1(3600);
 PWM1_SetCompare2(0);

}

if(SEARCH_L2_IO==1&&SEARCH_L1_IO==1&&SEARCH_M_IO==1&&SEARCH_R1_IO==1&&SEARCH_R2_IO==1){//最右边R2检测到，右转
     item1++;
	
	if(item1>=6){
 PWM1_SetCompare1(0);
    PWM1_SetCompare2(0);
}
  else{  PWM1_SetCompare1(0);
    PWM1_SetCompare2(0);
	  //搜寻打靶
	GPIO_ResetBits(GPIOE,GPIO_Pin_9);//触发蜂鸣器
	GPIO_ResetBits(GPIOE,GPIO_Pin_5);//低电平，灯光
    Delay_ms(1000);//停下来1s
	 GPIO_SetBits(GPIOE,GPIO_Pin_9);//关闭蜂鸣器
	GPIO_SetBits(GPIOE,GPIO_Pin_5);//输出高电平，关灯
	  PWM1_SetCompare1(3600);
    PWM1_SetCompare2(3600);
	   Delay_ms(600);//停下来0.6s
  }
}



//		if (key_val > 0 && key_val < 17){
//		printf("This is S%d key\r\n",key_val);	
//	}
			
			
			//ADValue=AD_GetValue();
			//ADValue=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1);
			//printf("capture is:%.3f\n",ADValue);
			
			
			//Delay_ms(100);
			//Voltage=(float)ADValue/4095*3.3;//转换为电压值
			//OLED_ShowNum(2,1,Target*100,5);
	        //OLED_ShowNum(4,1,Rev*100,5);
			//OLED_ShowNum(5,1,ADValue,4);
			//OLED_ShowNum(6,1,Voltage*100,4);
			//printf("%d, %d \r\n",moto,X);		
		}
		
	}
		  

  

