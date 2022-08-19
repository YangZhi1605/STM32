#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_adc.h"

extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];
//局部变量，用于保存转换计算后的电压值
float ADC_ConvertedValueLocal[NOFCHANEL];

#define SOFT_DELAY Delay(0xFFFFF);
//延时函数
void Delay(uint32_t count )
{
	for(; count!=0; count--);
}

/*
独立模式 —— 多通道-DMA读取只能在DMA1或者DMA3
1、初始化ADC用到的GPIO
2、初始化ADC初始化结构体
3、配置ADC时钟，配置通道的转换顺序和采样时间
4、使能ADC转换，完成中断，配置中断优先级
5、使能ADC，准备开始转换
6、校准ADC
7、软件触发ADC，真正开始转换
8、编写中断服务函数，读取ADC转换数据 —— 因为通过中断来读取的，所以需要到stm32f10x_it.c写中断服务函数
9、编写main函数，把转换数据打印出来
*/


int main(void)
{	
	//初始化USART，配置模式为115200 S-N-1，中断接受
	USART_Config();
	//初始化ADC
	ADCx_Init();
	
	
	//可以通过串口调试助手，把获得的数据，打印出来
	
	printf("\r\n ----这是一个ADC单通道中断读取实验----\r\n");
	
	while (1)
	{
			ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3;
			ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
			ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*3.3;
			ADC_ConvertedValueLocal[3] =(float) ADC_ConvertedValue[3]/4096*3.3;
			ADC_ConvertedValueLocal[4] =(float) ADC_ConvertedValue[4]/4096*3.3;
			ADC_ConvertedValueLocal[5] =(float) ADC_ConvertedValue[5]/4096*3.3;
		
			printf("\r\n CH0 value = %f V \r\n",ADC_ConvertedValueLocal[0]);
			printf("\r\n CH1 value = %f V \r\n",ADC_ConvertedValueLocal[1]);
			printf("\r\n CH2 value = %f V \r\n",ADC_ConvertedValueLocal[2]);
			printf("\r\n CH3 value = %f V \r\n",ADC_ConvertedValueLocal[3]);
			printf("\r\n CH4 value = %f V \r\n",ADC_ConvertedValueLocal[4]);
			printf("\r\n CH5 value = %f V \r\n",ADC_ConvertedValueLocal[5]);
		
			printf("\r\n\r\n");
			Delay(0xffffee);		 
	}
}



