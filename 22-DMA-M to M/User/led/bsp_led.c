//bsp:board support package �弶֧�ְ�
//�����漰��ͷ�ļ��ģ�����Ҫ�ڱ༭��ħ������ָ��·��
#include "bsp_led.h"

void LED_GPIO_Config(void)
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//����֮���̵Ƶ�ʱ����������棬��������Ҫ�ú����������ˣ�Ҫ���ַ�ʽ
	//RCC_APB2PeriphClockCmd(LED_G_GPIO_CLK, ENABLE) ;
	RCC_APB2PeriphClockCmd(LED_G_GPIO_CLK |
						   LED_B_GPIO_CLK |
						   LED_R_GPIO_CLK , ENABLE) ;
	
	//Ϊ����߳���Ŀ���ֲ��
	//�ͳ���Ӳ����صģ�������ɺ�
	//���罫����Ҫ�������̵Ƶ�������ͷ�ļ��ж���ɺ�
	GPIO_InitStruct.GPIO_Pin = LED_G_GPIO_PIN;
	
	//��ģʽ����Ϊ�������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
	//�����ٶ�
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//��������Щ��������GPIO�Ĵ��룬���ǿ�������̼����̵�
	
	//�˿����õͼĴ��� GPIOx_CRL
	/*���ÿ⺯������ʼ��GPIO*/
	//������Ҫ��ʼ����GPIO�˿� ���� ����������߼����������ã��ٳ�ʼ��
	GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStruct);
	
	//��ʱ����ҪRCC,���ڿ���ȥ�⺯����֪����Ӧ���ļ� ���� �ŵ���ʼ���ṹ��֮���߼��ȽϺ�
	//RCC_APB2PeriphClockCmd(LED_G_GPIO_CLK, ENABLE);
	
	//ͬ�����ú���Ѿ�����
	//��ȷ���˿ڡ��ٶȡ�ģʽ�����ú�����ʼ��
	/*ѡ��Ҫ���ƵĶ˿�*/
	GPIO_InitStruct.GPIO_Pin = LED_B_GPIO_PIN;
	//GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LED_R_GPIO_PIN;
	//GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStruct);
	
	//�ر����е�LED��
	GPIO_SetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);
	GPIO_SetBits(LED_R_GPIO_PORT,LED_R_GPIO_PIN);
	GPIO_SetBits(LED_B_GPIO_PORT,LED_B_GPIO_PIN);
	
	
}

