#include "stm32f10x.h" 
uint16_t MyDMA_Size;
void MyDMA_Init(uint32_t AddrA,uint32_t AddrB,uint16_t Size){
    MyDMA_Size=Size;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//开启DMA时钟
    DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr=AddrA;
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Enable;//外设寄存器三个参数
	DMA_InitStructure.DMA_MemoryBaseAddr=AddrB;
    DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;//存储器三个参数
    DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;//传输方向,外设到存储器
	DMA_InitStructure.DMA_BufferSize=Size;//缓冲区大小，传输计数器
	DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;//传输模式，是否自动重装,正常模式不自动重装
    DMA_InitStructure.DMA_M2M=DMA_M2M_Enable;//硬件/软件触发,这里是软件触发，存到存
    DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;//优先级
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1,DISABLE);//初始化后不会自动转运，需调用下方函数
}

void MyDMA_Transfer(void){//给传输计数器赋值
DMA_Cmd(DMA1_Channel1,DISABLE);//赋值前先关闭开关
DMA_SetCurrDataCounter(DMA1_Channel1,MyDMA_Size);
DMA_Cmd(DMA1_Channel1,ENABLE);
while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);//等待转运完成
DMA_ClearFlag(DMA1_FLAG_TC1);//清除标志位
}
