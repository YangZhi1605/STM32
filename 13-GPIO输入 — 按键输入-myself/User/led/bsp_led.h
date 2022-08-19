#ifndef _BSP_LED_H
#define _BSP_LED_H

#include "stm32f10x.h"

//使用按键，操作绿灯
#define LED_G_GPIO_PIN		GPIO_Pin_0
#define LED_G_GPIO_PORT		GPIOB
#define LED_G_GPIO_CLK		RCC_APB2Periph_GPIOB


//使用按键操作红灯
#define LED_R_GPIO_PIN		GPIO_Pin_5
#define LED_R_GPIO_PORT		GPIOB
#define LED_R_GPIO_CLK		RCC_APB2Periph_GPIOB

//这里需要用到反转，定义反转
//^异或运算实现翻转，^是不进位加法
#define LED_G_TOGGLE		{LED_G_GPIO_PORT->ODR ^= LED_G_GPIO_PIN;}
#define LED_R_TOGGLE		{LED_R_GPIO_PORT->ODR ^= LED_R_GPIO_PIN;}
void LED_GPIO_Config(void);


#endif /*_BSP_LED_H*/

