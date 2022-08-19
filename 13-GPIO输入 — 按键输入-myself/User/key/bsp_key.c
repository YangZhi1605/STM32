//����ͷ�ļ���ָ��ͷ�ļ�·��
#include "bsp_key.h"
#include "bsp_led.h"

void KEY_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//����ʲô���裬��ʼ��֮ǰ������Ҫ��ʱ��
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
* @brief   ����Ƿ��а�������
* @param  GPIOx:����Ķ˿�, x�����ǣ�A...G��
* @param  GPIO_PIN:����Ķ˿�λ�� ������GPIO_PIN_x��x������0...15��
* @retval  ������״̬
*     @arg KEY_ON:��������
*     @arg KEY_OFF:����û����
*/
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
    /*����Ƿ��а������� */
    if (GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) {
        /*�ȴ������ͷ�
		��ʹ��whileѭ��������ⰴ��״̬�� ֱ�������ͷţ�
		�����ͷź�Key_Scan��������һ����KEY_ON��ֵ����û�м�⵽�������£�����ֱ�ӷ��ء�KEY_OFF����
		��������Ӳ��û��������������Ҫ�����Key_Scan������������˲�����ֹ���ƶ��������󴥷���
		*/
        while (GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);
        return  KEY_ON;
    } else
        return KEY_OFF;
}


