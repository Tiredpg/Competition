#ifndef __PWM_H
#define __PWM_H

void PWM1_Init(uint16_t arr,uint16_t psc);
void PWM1_SetCompare1(uint16_t Compare1);
void PWM1_SetCompare2(uint16_t Compare2);
void PWM1_SetCompare3(uint16_t Compare3);
void PWM1_SetPrescaler(uint16_t Prescaler);

#endif

