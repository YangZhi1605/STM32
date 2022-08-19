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

上面是misc中写的关于NVIC分组的内容
大致是这种理解的，对于组0，就是四个位全部给子优先级，那么自己有的数位就是0，而子优先级这里就是四个位能够有0-15
组1就是，有一位给自己了，自己就可以表示到0-1，剩下的三位给子优先级，也就是0-7了。其他同理类推。

*/
//用static限制一下这个NVIC的作用域
static void EXTI_NVIC_Config(void)
{
	//同样是找到头文件中NVIC的相关信息
	//通过结构体+初始化函数的方式实现
	NVIC_InitTypeDef NVIC_InitStruct;
	
	//设置中断优先级的分组 —— 利用库函数 也是根据参数写了
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//至于为什么是组1，后面根据文档再看了
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;//配置主优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;//配置子优先级，在比较的时候，先比较主，主相同比较次，次相同比较IRQn枚举类型中的顺序
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct); 
}


void EXTI_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	
	//3、配置中断优先级 —— 这里应该是顺序上的三步，只是逻辑上，应该先放这里
	EXTI_NVIC_Config();
	
	
	//1、初始化要连接到EXTI的GPIO —— 可以通俗的说是选择线
	//首先也是开时钟
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin = KEY1_INT_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(KEY1_INT_GPIO_PORT,&GPIO_InitStruct);
	
	
	//2、初始化EXTI —— 通过GPIO中给的函数确定输入线
	//直接F12去看这个函数参数怎么用
	//通过系统架构图，可以发现，EXTI这个外设，在APB2上
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	
	//初始化EXTI这个结构体 —— 定义的变量，统一放在函数开头
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;//这儿是触发选择，即是上升沿还是下降沿产生中断。因为默认是低电平，按时之后是高电平，这就是上升沿
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	
	//通过EXTI的库函数，把上面确定的结构体成员写到相应的寄存器中，让它们起到实际的作用
	EXTI_Init(&EXTI_InitStruct);
	
	
	
}


