#include "stm32f10x.h"  //相当于51单片机中，#include <reg51.h>
#include "bsp_led.h"


void Delay(uint32_t count)
{
	for(;count !=0; count--);
}

int main()
{
    //来到这里的时候，系统时钟已经被配置成为了72M
	//调用写好的初始化函数
	LED_GPIO_Config();
	
	//置为高电平，灯就会熄灭
	//GPIO_SetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);
	//reset置为0，灯会亮
	//GPIO_ResetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);
	
	//让绿灯闪烁
	/*
	while(1)
	{
		//拓展一下带参宏 + C 语言的续行符
		//GPIO_SetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);
		LED_G(OFF);
		Delay(0xFFFFF);
		LED_G(ON);
		//GPIO_ResetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);
		Delay(0xFFFFF);
	}
	*/
	
	/*流水灯 + 彩色闪烁*/
	//等的GPIO初始化中，应该把所有的灯先关闭
	
	
	while(1)
	{
		//这儿是常规的打开红绿蓝+延时实现流水灯
		//红
		LEDR_ON;
		Delay(0xFFFFF);
		LEDR_OFF;
		
		//绿
		LEDG_ON;
		Delay(0xFFFFF);
		LEDG_OFF;
		
		//蓝
		LEDB_ON;
		Delay(0xFFFFF);
		LEDB_OFF;
		
		 /*
			轮流显示 红绿蓝黄紫青白 颜色
			这里需要组合一定的灯的颜色
		 */
		Delay(0xFFFFF);
		Delay(0xFFFFF);
		
		//红
		LED_RED;
		Delay(0xFFFFF);
		Delay(0xFFFFF);
		
		//绿
		LED_GREEN;
		Delay(0xFFFFF);
		Delay(0xFFFFF);
		
		//蓝
		LED_BLUE ;
		Delay(0xFFFFF);
		Delay(0xFFFFF);
		
		//黄
		LED_YELLOW;
		Delay(0xFFFFF);
		Delay(0xFFFFF);
		
		//紫
		LED_PURPLE;
		Delay(0xFFFFF);
		Delay(0xFFFFF);
		
		//青
		LED_CYAN;
		Delay(0xFFFFF);
		Delay(0xFFFFF);
		
		//白
		LED_WHITE;
		Delay(0xFFFFF);
		Delay(0xFFFFF);
		
		//关闭
		LED_RGBOFF;
		
	}
}

