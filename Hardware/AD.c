#include "stm32f10x.h" 

void AD_Init(void){//可结合DMA多通道，单次非扫描多通道
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//开启ADC1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使用PA0口
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//APB2的72M时钟选择2 4 6 8分频，输入到ADCCLK,ADCCLK=12MHZ
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//GPIO无效
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);//填写通道菜单，多次调用写多个通道
    
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;//连续转换模式，连续/单次转换，单次转换
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;//右对齐
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//外部触发源选择，内部软件触发
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;//工作模式，独立工作模式/双ADC模式
	ADC_InitStructure.ADC_NbrOfChannel=1;//扫描模式下的通道数目
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;//扫描/非扫描模式，非扫描单通道
	ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化
	
	ADC_Cmd(ADC1, ENABLE);//ADC开关控制，上电
	
ADC_ResetCalibration(ADC1);//复位校准
while(ADC_GetResetCalibrationStatus(ADC1)==SET);
	 //复位校准未完成，循环等待，0说明完成
 
 //获取复位校准状态
ADC_StartCalibration(ADC1);//开始校准
while(ADC_GetCalibrationStatus(ADC1)==SET);//开始校准未完成,循环等待，0说明完成
 
}


uint16_t AD_GetValue(void){
ADC_SoftwareStartConvCmd(ADC1, ENABLE);//软件触发转换，连续转换放在定义里面
while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);//获取标志位，判断转换结束（EOC=1），转换未完成，等待。连续转换不需要这句
return ADC_GetConversionValue(ADC1);//ADC获取数据寄存器
}




