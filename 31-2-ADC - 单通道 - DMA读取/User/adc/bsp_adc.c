#include "bsp_adc.h"

__IO uint16_t ADC_ConvertedValue;

//1����ʼ��ADC�õ���GPIO
static void ADCx_GPIO_Config(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	
	// �� ADC IO�˿�ʱ��
	ADC_GPIO_APBxClock_FUN ( ADC_GPIO_CLK, ENABLE );
	
	// ���� ADC IO ����ģʽ
	// ����Ϊģ������
	GPIO_InitStructure.GPIO_Pin = ADC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	
	// ��ʼ�� ADC IO
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);
}


//2����ʼ��ADC��ʼ���ṹ��
static void ADCx_Mode_Config(void)
{
	//�����ʼ���ṹ�� ���� ͨ��adc�⺯��
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStruct;

	// ��DMAʱ�� 
	RCC_AHBPeriphClockCmd(ADC_DMA_CLK, ENABLE);
	//��ADCʱ��
	ADC_APBxClock_FUN ( ADC_CLK, ENABLE );
	
	// ��λDMA������
	DMA_DeInit(ADC_DMA_CHANNEL);
	
	// ���� DMA ��ʼ���ṹ��
	// �����ַΪ��ADC ���ݼĴ�����ַ
	DMA_InitStructure.DMA_PeripheralBaseAddr = ( uint32_t ) ( & ( ADC_x->DR ) );
	 
	// �洢����ַ��ʵ���Ͼ���һ���ڲ�SRAM�ı���
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertedValue;
	
	// ����Դ��������
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	// ��������СΪ1���������Ĵ�СӦ�õ��ڴ洢���Ĵ�С
	DMA_InitStructure.DMA_BufferSize = 1;
	
	// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	// �洢����ַ�̶�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; 
	
	// �������ݴ�СΪ���֣��������ֽ�
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	
	// �洢�����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	
	// ѭ������ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	

	// DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
	// ��ֹ�洢�����洢��ģʽ����Ϊ�Ǵ����赽�洢��
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	// ��ʼ��DMA
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);
	
	// ʹ�� DMA ͨ��
	DMA_Cmd(ADC_DMA_CHANNEL , ENABLE);
	
	/********************************************************************/
	
	//ѡ��ģʽ
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ;
	
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	
	ADC_InitStruct.ADC_NbrOfChannel = 1;
	
	
	//void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
	ADC_Init(ADC_x,&ADC_InitStruct);
	
	//3������ADCʱ�ӣ�����ͨ����ת��˳��Ͳ���ʱ�� ���� �ɹ̼��⺯�����
	//void RCC_ADCCLKConfig(uint32_t RCC_PCLK2)
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	//void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
	ADC_RegularChannelConfig(ADC_x,ADC_CHANNEL,1, ADC_SampleTime_55Cycles5);
	
	
	//ʹ��DMA������
	//void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState);
	ADC_DMACmd(ADC_x,ENABLE);
	//5��ʹ��ADC��׼����ʼת��
	//void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
	ADC_Cmd(ADC_x,ENABLE);
	
	//6��У׼ADC
	ADC_ResetCalibration(ADC_x);
	// �ȴ�У׼�Ĵ�����ʼ�����
	while(ADC_GetResetCalibrationStatus(ADC_x));
	
	//7���������ADC��������ʼת��
	// ADC��ʼУ׼
	ADC_StartCalibration(ADC_x);
	// �ȴ�У׼���
	while(ADC_GetCalibrationStatus(ADC_x));
	// ����û�в����ⲿ����������ʹ���������ADCת�� 
	ADC_SoftwareStartConvCmd(ADC_x, ENABLE);
}


//дADC��ʼ��������������Ĳ������ܺ�����
void ADCx_Init(void)
{
	//Ϊ�˷�ֹ�������������������ã�ʹ��static����һ��
	//����GPIO
	ADCx_GPIO_Config();
	//�����ù���ģʽ
	ADCx_Mode_Config();
	
}



