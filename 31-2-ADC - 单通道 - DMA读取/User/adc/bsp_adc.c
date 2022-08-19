#include "bsp_adc.h"

__IO uint16_t ADC_ConvertedValue;

//1、初始化ADC用到的GPIO
static void ADCx_GPIO_Config(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	
	// 打开 ADC IO端口时钟
	ADC_GPIO_APBxClock_FUN ( ADC_GPIO_CLK, ENABLE );
	
	// 配置 ADC IO 引脚模式
	// 必须为模拟输入
	GPIO_InitStructure.GPIO_Pin = ADC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	
	// 初始化 ADC IO
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);
}


//2、初始化ADC初始化结构体
static void ADCx_Mode_Config(void)
{
	//定义初始化结构体 —— 通过adc库函数
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStruct;

	// 打开DMA时钟 
	RCC_AHBPeriphClockCmd(ADC_DMA_CLK, ENABLE);
	//打开ADC时钟
	ADC_APBxClock_FUN ( ADC_CLK, ENABLE );
	
	// 复位DMA控制器
	DMA_DeInit(ADC_DMA_CHANNEL);
	
	// 配置 DMA 初始化结构体
	// 外设基址为：ADC 数据寄存器地址
	DMA_InitStructure.DMA_PeripheralBaseAddr = ( uint32_t ) ( & ( ADC_x->DR ) );
	 
	// 存储器地址，实际上就是一个内部SRAM的变量
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertedValue;
	
	// 数据源来自外设
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	// 缓冲区大小为1，缓冲区的大小应该等于存储器的大小
	DMA_InitStructure.DMA_BufferSize = 1;
	
	// 外设寄存器只有一个，地址不用递增
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	// 存储器地址固定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; 
	
	// 外设数据大小为半字，即两个字节
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	
	// 存储器数据大小也为半字，跟外设数据大小相同
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	
	// 循环传输模式
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	

	// DMA 传输通道优先级为高，当使用一个DMA通道时，优先级设置不影响
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
	// 禁止存储器到存储器模式，因为是从外设到存储器
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	// 初始化DMA
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);
	
	// 使能 DMA 通道
	DMA_Cmd(ADC_DMA_CHANNEL , ENABLE);
	
	/********************************************************************/
	
	//选择模式
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ;
	
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	
	ADC_InitStruct.ADC_NbrOfChannel = 1;
	
	
	//void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
	ADC_Init(ADC_x,&ADC_InitStruct);
	
	//3、配置ADC时钟，配置通道的转换顺序和采样时间 —— 由固件库函数完成
	//void RCC_ADCCLKConfig(uint32_t RCC_PCLK2)
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	//void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
	ADC_RegularChannelConfig(ADC_x,ADC_CHANNEL,1, ADC_SampleTime_55Cycles5);
	
	
	//使能DMA的请求
	//void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState);
	ADC_DMACmd(ADC_x,ENABLE);
	//5、使能ADC，准备开始转换
	//void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
	ADC_Cmd(ADC_x,ENABLE);
	
	//6、校准ADC
	ADC_ResetCalibration(ADC_x);
	// 等待校准寄存器初始化完成
	while(ADC_GetResetCalibrationStatus(ADC_x));
	
	//7、软件触发ADC，真正开始转换
	// ADC开始校准
	ADC_StartCalibration(ADC_x);
	// 等待校准完成
	while(ADC_GetCalibrationStatus(ADC_x));
	// 由于没有采用外部触发，所以使用软件触发ADC转换 
	ADC_SoftwareStartConvCmd(ADC_x, ENABLE);
}


//写ADC初始化函数，把上面的操作，总和起来
void ADCx_Init(void)
{
	//为了防止这三个函数被其他调用，使用static修饰一下
	//配置GPIO
	ADCx_GPIO_Config();
	//再配置工作模式
	ADCx_Mode_Config();
	
}



