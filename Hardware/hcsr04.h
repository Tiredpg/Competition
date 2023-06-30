#ifndef __HCSR04_H
#define __HCSR04_H
#include "stm32f10x.h"
#include "delay.h"

#define HCSR04_PORT    	   GPIOB
#define HCSR04_CLK    	   RCC_APB2Periph_GPIOB
#define HCSR04_TIM_CLK     RCC_APB1Periph_TIM2
#define HCSR04_TRIG   	   GPIO_Pin_7
#define HCSR04_ECHO        GPIO_Pin_6

void hcsr04Init(void);
float UltraSonic_valuetance(void);



#endif
