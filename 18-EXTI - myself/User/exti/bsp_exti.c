#include "bsp_exti.h"


/**
@code  
 The table below gives the allowed values of the pre-emption priority and subpriority according
 to the Priority Grouping configuration performed by NVIC_PriorityGroupConfig function
  ============================================================================================================================
    NVIC_PriorityGroup   | NVIC_IRQChannelPreemptionPriority | NVIC_IRQChannelSubPriority  | Description
  ============================================================================================================================
   NVIC_PriorityGroup_0  |                0                  |            0-15             |   0 bits for pre-emption priority
                         |                                   |                             |   4 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------
   NVIC_PriorityGroup_1  |                0-1                |            0-7              |   1 bits for pre-emption priority
                         |                                   |                             |   3 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_2  |                0-3                |            0-3              |   2 bits for pre-emption priority
                         |                                   |                             |   2 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_3  |                0-7                |            0-1              |   3 bits for pre-emption priority
                         |                                   |                             |   1 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_4  |                0-15               |            0                |   4 bits for pre-emption priority
                         |                                   |                             |   0 bits for subpriority                       
  ============================================================================================================================
@endcode

������misc��д�Ĺ���NVIC���������
�������������ģ�������0�������ĸ�λȫ���������ȼ�����ô�Լ��е���λ����0���������ȼ���������ĸ�λ�ܹ���0-15
��1���ǣ���һλ���Լ��ˣ��Լ��Ϳ��Ա�ʾ��0-1��ʣ�µ���λ�������ȼ���Ҳ����0-7�ˡ�����ͬ�����ơ�

*/
//��static����һ�����NVIC��������
static void EXTI_NVIC_Config(void)
{
	//ͬ�����ҵ�ͷ�ļ���NVIC�������Ϣ
	//ͨ���ṹ��+��ʼ�������ķ�ʽʵ��
	NVIC_InitTypeDef NVIC_InitStruct;
	
	//�����ж����ȼ��ķ��� ���� ���ÿ⺯�� Ҳ�Ǹ��ݲ���д��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//����Ϊʲô����1����������ĵ��ٿ���
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;//���������ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;//���������ȼ����ڱȽϵ�ʱ���ȱȽ���������ͬ�ȽϴΣ�����ͬ�Ƚ�IRQnö�������е�˳��
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct); 
}


void EXTI_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	
	//3�������ж����ȼ� ���� ����Ӧ����˳���ϵ�������ֻ���߼��ϣ�Ӧ���ȷ�����
	EXTI_NVIC_Config();
	
	
	//1����ʼ��Ҫ���ӵ�EXTI��GPIO ���� ����ͨ�׵�˵��ѡ����
	//����Ҳ�ǿ�ʱ��
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = KEY1_INT_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(KEY1_INT_GPIO_PORT,&GPIO_InitStruct);
	
	
	//2����ʼ��EXTI ���� ͨ��GPIO�и��ĺ���ȷ��������
	//ֱ��F12ȥ���������������ô��
	//ͨ��ϵͳ�ܹ�ͼ�����Է��֣�EXTI������裬��APB2��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	
	//��ʼ��EXTI����ṹ�� ���� ����ı�����ͳһ���ں�����ͷ
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;//����Ǵ���ѡ�񣬼��������ػ����½��ز����жϡ���ΪĬ���ǵ͵�ƽ����ʱ֮���Ǹߵ�ƽ�������������
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	
	//ͨ��EXTI�Ŀ⺯����������ȷ���Ľṹ���Աд����Ӧ�ļĴ����У���������ʵ�ʵ�����
	EXTI_Init(&EXTI_InitStruct);
	
	
	
}


