#include "bsp_adc.h"

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
	ADC_InitTypeDef ADC_InitStruct;

	//打开ADC时钟
	ADC_APBxClock_FUN ( ADC_CLK, ENABLE );
	
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
	
	
	//4、使能ADC转换，完成中断，配置中断优先级 —— 由固件库函数完成
	//void ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState);
	ADC_ITConfig(ADC_x,ADC_IT_EOC,ENABLE);
	
	
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

//第四步的配置中断优先级
static void ADCx_NVIC_Config(void)
{
	  NVIC_InitTypeDef NVIC_InitStructure;
	  // 优先级分组
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	  // 配置中断优先级
	  NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQ;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
}

//写ADC初始化函数，把上面的操作，总和起来
void ADCx_Init(void)
{
	//为了防止这三个函数被其他调用，使用static修饰一下
	//先把GPIO的优先级配置了
	ADCx_NVIC_Config();
	//配置GPIO
	ADCx_GPIO_Config();
	//再配置工作模式
	ADCx_Mode_Config();
	
}



