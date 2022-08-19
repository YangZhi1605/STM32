//Ϊ�˷�ֹ���ͷ�ļ��ڱ��������õ�ʱ������ظ�����
//ʹ�����º궨��
#ifndef _BSP_LED_H
#define _BSP_LED_H

#include "stm32f10x.h"

//���̵���Ҫ�����Ķ˿�0�������ΪLED_G_GPIO_PIN
#define LED_G_GPIO_PIN		GPIO_Pin_0 //#define GPIO_Pin_0                 ((uint16_t)0x0001)  /*!< Pin 0 selected */ ���Ƕ�����gpio.hͷ�ļ��е�����
#define LED_G_GPIO_PORT		GPIOB      //#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE) Ҳ����gpio.h�У���ֱ��F12�鿴��
#define LED_G_GPIO_CLK		RCC_APB2Periph_GPIOB 

//����ͬ���ķ�ʽ�����ƺ�����
#define LED_R_GPIO_PIN		GPIO_Pin_5 
#define LED_R_GPIO_PORT		GPIOB      
#define LED_R_GPIO_CLK		RCC_APB2Periph_GPIOB 

#define LED_B_GPIO_PIN		GPIO_Pin_1
#define LED_B_GPIO_PORT		GPIOB      
#define LED_B_GPIO_CLK		RCC_APB2Periph_GPIOB 



#define ON					1
#define OFF					0
//C�����У����з�����ֻ�ܸ��س���
//#define LED_G(a)		if(a) GPIO_ResetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);else GPIO_SetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);
#define LED_G(a)		if(a)\
							GPIO_ResetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);\
						else GPIO_SetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);



/*��չ�淨 ���� �ʵ�*/

/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define digitalHi(p,i)       {p->BSRR=i;}    //���Ϊ�ߵ�ƽ
#define digitalLo(p,i)       {p->BRR=i;}     //����͵�ƽ
#define digitalToggle(p,i)   {p->ODR ^=i;}   //�����ת״̬


/* �������IO�ĺ� */
#define LEDR_TOGGLE       digitalToggle(LED_R_GPIO_PORT,LED_R_GPIO_PIN)
#define LEDR_OFF          digitalHi(LED_R_GPIO_PORT,LED_R_GPIO_PIN)
#define LEDR_ON           digitalLo(LED_R_GPIO_PORT,LED_R_GPIO_PIN)

#define LEDG_TOGGLE       digitalToggle(LED_G_GPIO_PORT,LED_G_GPIO_PIN)
#define LEDG_OFF          digitalHi(LED_G_GPIO_PORT,LED_G_GPIO_PIN)
#define LEDG_ON           digitalLo(LED_G_GPIO_PORT,LED_G_GPIO_PIN)

#define LEDB_TOGGLE       digitalToggle(LED_B_GPIO_PORT,LED_B_GPIO_PIN)
#define LEDB_OFF          digitalHi(LED_B_GPIO_PORT,LED_B_GPIO_PIN)
#define LEDB_ON           digitalLo(LED_B_GPIO_PORT,LED_B_GPIO_PIN)

/* ������ɫ������߼��÷�ʹ��PWM�ɻ��ȫ����ɫ,��Ч������ */

//��
#define LED_RED  \
                    LEDR_ON;\
                    LEDG_OFF\
                    LEDB_OFF

//��
#define LED_GREEN       \
                    LEDR_OFF;\
                    LEDG_ON\
                    LEDB_OFF

//��
#define LED_BLUE    \
                    LEDR_OFF;\
                    LEDG_OFF\
                    LEDB_ON


//��(��+��)
#define LED_YELLOW  \
                    LEDR_ON;\
                    LEDG_ON\
                    LEDB_OFF
//��(��+��)
#define LED_PURPLE  \
                    LEDR_ON;\
                    LEDG_OFF\
                    LEDB_ON

//��(��+��)
#define LED_CYAN \
                    LEDR_OFF;\
                    LEDG_ON\
                    LEDB_ON

//��(��+��+��)
#define LED_WHITE   \
                    LEDR_ON;\
                    LEDG_ON\
                    LEDB_ON

//��(ȫ���ر�)
#define LED_RGBOFF  \
                    LEDR_OFF;\
                    LEDG_OFF\
                    LEDB_OFF





//����bsp_led.c���õ��ĺ���
void LED_GPIO_Config(void);

#endif /*_BSP_LED_H*/


