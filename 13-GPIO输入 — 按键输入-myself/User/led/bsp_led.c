#include "bsp_led.h"

void LED_GPIO_Config(void)
{
	//声明一个GPIO初始化类型的结构体
	//GPIO_InitTypeDef* GPIO_InitStruct;
	//这里只是定义这种类型的结构体。不是相应类型的指针
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//启动GPIO外设时钟，不要忘记了
	RCC_APB2PeriphClockCmd(LED_G_GPIO_CLK|
						   LED_R_GPIO_CLK,ENABLE);
	
	//确定端口的引脚信息
//	GPIO_InitStruct->GPIO_Pin = LED_G_GPIO_PIN;
	//确实输出模式
//	GPIO_InitStruct->GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStruct->GPIO_Speed = GPIO_Speed_50MHz;
	
	//发现新错误，应该是.运算符,->应该是指针中用的 —— 数据结构那儿
	GPIO_InitStruct.GPIO_Pin = LED_G_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//调用初始化的库函数
	//GPIO_Init(LED_G_GPIO_PIN, &GPIO_InitStruct);
	//void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
	//注意理解这里的逻辑，这里第一个参数是让指定A-G的端口了，后面的GPIO_InitStruct在上面代码中固定好了该端口下的哪个引脚，速度，模式
	GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStruct); 
	
	GPIO_InitStruct.GPIO_Pin = LED_R_GPIO_PIN;
	GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStruct); 
	
	//先关闭所有LED灯
	GPIO_SetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);
	GPIO_SetBits(LED_R_GPIO_PORT,LED_R_GPIO_PIN);
	
	
}


