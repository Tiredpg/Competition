#ifndef __ENCODER_H
#define __ENCODER_H
void Encoder_Init(void);
uint16_t Encoder_GetTIM4(void);
int Read_Encoder(uint8_t TIMX);
void TIM2_IRQHandler(void);
uint16_t Encoder_GetTIM3(void);
#endif
