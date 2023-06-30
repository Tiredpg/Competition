#ifndef __SERIAL_H
#define __SERIAL_H
#include <stdio.h>
void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array,uint16_t Length);
void Serial_SendString(char *String);
uint32_t Serial_Pow(uint32_t X, uint32_t Y);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
//int fputc(int ch, FILE *f); usart已经封装过
void Serial_Printf(char *format, ...);
double Get_ReceiveData(void);
#endif
