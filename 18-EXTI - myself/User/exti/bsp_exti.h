//差不多是头文件开始使用前的标准操作了
#ifndef _BSP_EXTI_H 
#define _BSP_EXTI_H

#include "stm32f10x.h" 

//老规矩，和硬件相关的，就定义为宏
#define KEY1_INT_GPIO_PIN		GPIO_Pin_0
#define KEY1_INT_GPIO_PORT		GPIOA
#define KEY1_INT_GPIO_CLK		RCC_APB2Periph_GPIOA


static void EXTI_NVIC_Config(void);
void EXTI_Key_Config(void);

#endif /*_BSP_EXTI_H*/

