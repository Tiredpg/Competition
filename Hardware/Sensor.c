#include "stm32f10x.h" 
void Sensor_GpioInit(void){

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//��һ���������԰�λ�����ö��ʱ��
	GPIO_InitTypeDef GPIO_InitStructure1;
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;//��λ�����ܽţ�allѡ��ȫ���ܽ�
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IPU;//��������
	GPIO_Init(GPIOE,&GPIO_InitStructure1);//���ö˿�ģʽ*/
	GPIO_SetBits(GPIOE,GPIO_Pin_5);//����ߵ�ƽ���ص�
	GPIO_SetBits(GPIOE,GPIO_Pin_9);//����ߵ�ƽ���ط�����
	GPIO_ResetBits(GPIOE,GPIO_Pin_9);//����͵�ƽ���ؼ����
	
}