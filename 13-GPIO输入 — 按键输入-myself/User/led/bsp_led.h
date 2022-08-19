#ifndef _BSP_LED_H
#define _BSP_LED_H

#include "stm32f10x.h"

//ʹ�ð����������̵�
#define LED_G_GPIO_PIN		GPIO_Pin_0
#define LED_G_GPIO_PORT		GPIOB
#define LED_G_GPIO_CLK		RCC_APB2Periph_GPIOB


//ʹ�ð����������
#define LED_R_GPIO_PIN		GPIO_Pin_5
#define LED_R_GPIO_PORT		GPIOB
#define LED_R_GPIO_CLK		RCC_APB2Periph_GPIOB

//������Ҫ�õ���ת�����巴ת
//^�������ʵ�ַ�ת��^�ǲ���λ�ӷ�
#define LED_G_TOGGLE		{LED_G_GPIO_PORT->ODR ^= LED_G_GPIO_PIN;}
#define LED_R_TOGGLE		{LED_R_GPIO_PORT->ODR ^= LED_R_GPIO_PIN;}
void LED_GPIO_Config(void);


#endif /*_BSP_LED_H*/

