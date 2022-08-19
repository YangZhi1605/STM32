#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_adc.h"

extern __IO uint16_t ADC_ConvertedValue;
//�ֲ����������ڱ���ת�������ĵ�ѹֵ
float ADC_ConvertedValueLocal;

#define SOFT_DELAY Delay(0xFFFFF);
//��ʱ����
void Delay(uint32_t count )
{
	for(; count!=0; count--);
}

/*
����ģʽ ���� ��ͨ��-�ж϶�ȡ
1����ʼ��ADC�õ���GPIO
2����ʼ��ADC��ʼ���ṹ��
3������ADCʱ�ӣ�����ͨ����ת��˳��Ͳ���ʱ��
4��ʹ��ADCת��������жϣ������ж����ȼ�
5��ʹ��ADC��׼����ʼת��
6��У׼ADC
7���������ADC��������ʼת��
8����д�жϷ���������ȡADCת������ ���� ��Ϊͨ���ж�����ȡ�ģ�������Ҫ��stm32f10x_it.cд�жϷ�����
9����дmain��������ת�����ݴ�ӡ����
*/


int main(void)
{	
	//��ʼ��USART������ģʽΪ115200 S-N-1���жϽ���
	USART_Config();
	//��ʼ��ADC
	ADCx_Init();
	
	
	//����ͨ�����ڵ������֣��ѻ�õ����ݣ���ӡ����
	
	printf("\r\n ----����һ��ADC��ͨ���ж϶�ȡʵ��----\r\n");
	
	while (1)
	{
		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; 
	
		printf("\r\n The current AD value = 0x%04X \r\n", 
		       ADC_ConvertedValue); 
		printf("\r\n The current AD value = %f V \r\n",
		       ADC_ConvertedValueLocal); 
		printf("\r\n\r\n");

		Delay(0xffffee);  
	}
}



