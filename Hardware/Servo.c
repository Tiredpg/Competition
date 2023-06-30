#include "stm32f10x.h"
#include   "PWM.h"
void Servo_Init(void){//舵机初始化


//PWM_Init(7200,1);

}

void Servo_SetAngle(float Angle){//直接传角度，范围0-180，不能超出


//PWM_SetCompare2(Angle/180*2000+500);//角度映射到通道CCR值

}
