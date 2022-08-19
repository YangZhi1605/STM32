#include "bsp_led.h"

void LED_GPIO_Config(void)
{
	//����һ��GPIO��ʼ�����͵Ľṹ��
	//GPIO_InitTypeDef* GPIO_InitStruct;
	//����ֻ�Ƕ����������͵Ľṹ�塣������Ӧ���͵�ָ��
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//����GPIO����ʱ�ӣ���Ҫ������
	RCC_APB2PeriphClockCmd(LED_G_GPIO_CLK|
						   LED_R_GPIO_CLK,ENABLE);
	
	//ȷ���˿ڵ�������Ϣ
//	GPIO_InitStruct->GPIO_Pin = LED_G_GPIO_PIN;
	//ȷʵ���ģʽ
//	GPIO_InitStruct->GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStruct->GPIO_Speed = GPIO_Speed_50MHz;
	
	//�����´���Ӧ����.�����,->Ӧ����ָ�����õ� ���� ���ݽṹ�Ƕ�
	GPIO_InitStruct.GPIO_Pin = LED_G_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//���ó�ʼ���Ŀ⺯��
	//GPIO_Init(LED_G_GPIO_PIN, &GPIO_InitStruct);
	//void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
	//ע�����������߼��������һ����������ָ��A-G�Ķ˿��ˣ������GPIO_InitStruct����������й̶����˸ö˿��µ��ĸ����ţ��ٶȣ�ģʽ
	GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStruct); 
	
	GPIO_InitStruct.GPIO_Pin = LED_R_GPIO_PIN;
	GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStruct); 
	
	//�ȹر�����LED��
	GPIO_SetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);
	GPIO_SetBits(LED_R_GPIO_PORT,LED_R_GPIO_PIN);
	
	
}


