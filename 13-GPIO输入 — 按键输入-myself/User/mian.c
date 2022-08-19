#include "stm32f10x.h"  //相当于51单片机中，#include <reg51.h>
#include "bsp_key.h"
#include "bsp_led.h"

//涉及按键都是需要软件消抖的 —— 延时解决
//输入涉及的寄存器是IDR

void Delay(uint32_t count)
{
	for(;count != 0; count--);
}

int main()
{
    //来到这里的时候，系统时钟已经被配置成为了72M
	//初始化LED端口
	LED_GPIO_Config();
	//初始化按键
	KEY_GPIO_Config();
	
	while(1)
	{
		if(Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON)
			LED_G_TOGGLE;
		
		if(Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON)
			LED_R_TOGGLE;
	}
}


