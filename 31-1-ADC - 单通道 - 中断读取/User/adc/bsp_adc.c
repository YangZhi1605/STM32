#include "bsp_adc.h"

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
	ADC_InitTypeDef ADC_InitStruct;

	//��ADCʱ��
	ADC_APBxClock_FUN ( ADC_CLK, ENABLE );
	
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
	
	
	//4��ʹ��ADCת��������жϣ������ж����ȼ� ���� �ɹ̼��⺯�����
	//void ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState);
	ADC_ITConfig(ADC_x,ADC_IT_EOC,ENABLE);
	
	
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

//���Ĳ��������ж����ȼ�
static void ADCx_NVIC_Config(void)
{
	  NVIC_InitTypeDef NVIC_InitStructure;
	  // ���ȼ�����
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	  // �����ж����ȼ�
	  NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQ;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
}

//дADC��ʼ��������������Ĳ������ܺ�����
void ADCx_Init(void)
{
	//Ϊ�˷�ֹ�������������������ã�ʹ��static����һ��
	//�Ȱ�GPIO�����ȼ�������
	ADCx_NVIC_Config();
	//����GPIO
	ADCx_GPIO_Config();
	//�����ù���ģʽ
	ADCx_Mode_Config();
	
}



