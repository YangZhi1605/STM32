//bsp:board support package 板级支持包
//但凡涉及到头文件的，都需要在编辑器魔术棒中指定路径
#include "bsp_led.h"

void LED_GPIO_Config(void)
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//单纯之后绿灯的时候可以这种玩，但是现在要用红绿蓝三种了，要换种方式
	//RCC_APB2PeriphClockCmd(LED_G_GPIO_CLK, ENABLE) ;
	RCC_APB2PeriphClockCmd(LED_G_GPIO_CLK |
						   LED_B_GPIO_CLK |
						   LED_R_GPIO_CLK , ENABLE) ;
	
	//为了提高程序的可移植性
	//和程序硬件相关的，都定义成宏
	//比如将这里要操作的绿灯的引脚在头文件中定义成宏
	GPIO_InitStruct.GPIO_Pin = LED_G_GPIO_PIN;
	
	//将模式设置为推挽输出
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
	//配置速度
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//上述的这些用于配置GPIO的代码，都是可以面向固件库编程的
	
	//端口配置低寄存器 GPIOx_CRL
	/*调用库函数，初始化GPIO*/
	//传入需要初始化的GPIO端口 —— 按照这儿的逻辑，是先设置，再初始化
	GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStruct);
	
	//开时钟需要RCC,现在可以去库函数中知道相应的文件 —— 放到初始化结构体之后，逻辑比较好
	//RCC_APB2PeriphClockCmd(LED_G_GPIO_CLK, ENABLE);
	
	//同理配置红灯已经蓝灯
	//先确定端口、速度、模式，再用函数初始化
	/*选择要控制的端口*/
	GPIO_InitStruct.GPIO_Pin = LED_B_GPIO_PIN;
	//GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LED_R_GPIO_PIN;
	//GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStruct);
	
	//关闭所有的LED灯
	GPIO_SetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);
	GPIO_SetBits(LED_R_GPIO_PORT,LED_R_GPIO_PIN);
	GPIO_SetBits(LED_B_GPIO_PORT,LED_B_GPIO_PIN);
	
	
}

