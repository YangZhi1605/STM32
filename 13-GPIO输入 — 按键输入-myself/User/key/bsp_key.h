#ifndef _BSP_KEY_H
#define _BSP_KEY_H


#include "stm32f10x.h"

//老规矩，使用宏来封装和硬件相关的代码
#define KEY1_GPIO_PIN		GPIO_Pin_0
#define KEY1_GPIO_PORT		GPIOA
#define KEY1_GPIO_CLK		RCC_APB2Periph_GPIOA

//现在来封装按键2
#define KEY2_GPIO_PIN		GPIO_Pin_13
#define KEY2_GPIO_PORT		GPIOC
#define KEY2_GPIO_CLK		RCC_APB2Periph_GPIOC


#define KEY_ON				1
#define KEY_OFF				0


void KEY_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
#endif /*_BSP_KEY_H*/

