//为了防止这个头文件在被其他调用的时候出现重复编译
//使用如下宏定义
#ifndef _BSP_LED_H
#define _BSP_LED_H

#include "stm32f10x.h"

//将绿灯需要依赖的端口0，定义成为LED_G_GPIO_PIN
#define LED_G_GPIO_PIN		GPIO_Pin_0 //#define GPIO_Pin_0                 ((uint16_t)0x0001)  /*!< Pin 0 selected */ 这是定义在gpio.h头文件中的内容
#define LED_G_GPIO_PORT		GPIOB      //#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE) 也是在gpio.h中，可直接F12查看的
#define LED_G_GPIO_CLK		RCC_APB2Periph_GPIOB 

//按照同样的方式定义红灯和蓝灯
#define LED_R_GPIO_PIN		GPIO_Pin_5 
#define LED_R_GPIO_PORT		GPIOB      
#define LED_R_GPIO_CLK		RCC_APB2Periph_GPIOB 

#define LED_B_GPIO_PIN		GPIO_Pin_1
#define LED_B_GPIO_PORT		GPIOB      
#define LED_B_GPIO_CLK		RCC_APB2Periph_GPIOB 



#define ON					1
#define OFF					0
//C语言中，续行符后面只能跟回车。
//#define LED_G(a)		if(a) GPIO_ResetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);else GPIO_SetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);
#define LED_G(a)		if(a)\
							GPIO_ResetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);\
						else GPIO_SetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);



/*拓展玩法 —— 彩灯*/

/* 直接操作寄存器的方法控制IO */
#define digitalHi(p,i)       {p->BSRR=i;}    //输出为高电平
#define digitalLo(p,i)       {p->BRR=i;}     //输出低电平
#define digitalToggle(p,i)   {p->ODR ^=i;}   //输出反转状态


/* 定义控制IO的宏 */
#define LEDR_TOGGLE       digitalToggle(LED_R_GPIO_PORT,LED_R_GPIO_PIN)
#define LEDR_OFF          digitalHi(LED_R_GPIO_PORT,LED_R_GPIO_PIN)
#define LEDR_ON           digitalLo(LED_R_GPIO_PORT,LED_R_GPIO_PIN)

#define LEDG_TOGGLE       digitalToggle(LED_G_GPIO_PORT,LED_G_GPIO_PIN)
#define LEDG_OFF          digitalHi(LED_G_GPIO_PORT,LED_G_GPIO_PIN)
#define LEDG_ON           digitalLo(LED_G_GPIO_PORT,LED_G_GPIO_PIN)

#define LEDB_TOGGLE       digitalToggle(LED_B_GPIO_PORT,LED_B_GPIO_PIN)
#define LEDB_OFF          digitalHi(LED_B_GPIO_PORT,LED_B_GPIO_PIN)
#define LEDB_ON           digitalLo(LED_B_GPIO_PORT,LED_B_GPIO_PIN)

/* 基本混色，后面高级用法使用PWM可混出全彩颜色,且效果更好 */

//红
#define LED_RED  \
                    LEDR_ON;\
                    LEDG_OFF\
                    LEDB_OFF

//绿
#define LED_GREEN       \
                    LEDR_OFF;\
                    LEDG_ON\
                    LEDB_OFF

//蓝
#define LED_BLUE    \
                    LEDR_OFF;\
                    LEDG_OFF\
                    LEDB_ON


//黄(红+绿)
#define LED_YELLOW  \
                    LEDR_ON;\
                    LEDG_ON\
                    LEDB_OFF
//紫(红+蓝)
#define LED_PURPLE  \
                    LEDR_ON;\
                    LEDG_OFF\
                    LEDB_ON

//青(绿+蓝)
#define LED_CYAN \
                    LEDR_OFF;\
                    LEDG_ON\
                    LEDB_ON

//白(红+绿+蓝)
#define LED_WHITE   \
                    LEDR_ON;\
                    LEDG_ON\
                    LEDB_ON

//黑(全部关闭)
#define LED_RGBOFF  \
                    LEDR_OFF;\
                    LEDG_OFF\
                    LEDB_OFF





//放置bsp_led.c中用到的函数
void LED_GPIO_Config(void);

#endif /*_BSP_LED_H*/


