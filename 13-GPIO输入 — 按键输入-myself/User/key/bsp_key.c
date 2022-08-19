//引入头文件，指定头文件路径
#include "bsp_key.h"
#include "bsp_led.h"

void KEY_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//不管什么外设，初始化之前，都需要开时钟
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK|
					       KEY2_GPIO_CLK,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = KEY1_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY1_GPIO_PORT,&GPIO_InitStruct);
	
	
	
	GPIO_InitStruct.GPIO_Pin = KEY2_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY2_GPIO_PORT,&GPIO_InitStruct);
	
	
}


/**
* @brief   检测是否有按键按下
* @param  GPIOx:具体的端口, x可以是（A...G）
* @param  GPIO_PIN:具体的端口位， 可以是GPIO_PIN_x（x可以是0...15）
* @retval  按键的状态
*     @arg KEY_ON:按键按下
*     @arg KEY_OFF:按键没按下
*/
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
    /*检测是否有按键按下 */
    if (GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) {
        /*等待按键释放
		则使用while循环持续检测按键状态， 直到按键释放，
		按键释放后Key_Scan函数返回一个“KEY_ON”值；若没有检测到按键按下，则函数直接返回“KEY_OFF”。
		若按键的硬件没有做消抖处理，需要在这个Key_Scan函数中做软件滤波，防止波纹抖动引起误触发。
		*/
        while (GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);
        return  KEY_ON;
    } else
        return KEY_OFF;
}


