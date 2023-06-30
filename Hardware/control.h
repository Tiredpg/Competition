#ifndef __CONTROL_H
#define __CONTROL_H
int Incremental_PI(int X,int Target);
void xianfu(void);
int myabs(int a);
void Set_Pwm(int moto);
void TIM5_IRQHandler(void);
#endif
