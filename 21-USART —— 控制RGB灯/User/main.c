#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_usart.h"


//#define SOFT_DELAY Delay(0xFFFFF);
/*
1����ʼ��������Ҫ�õ���GPIO
2����ʼ�����ڣ�USART_InitTypeDef
3���ж�����(�����жϣ��ж����ȼ�)
4��ʹ�ܴ���
5����д���ͺͽ��պ���
6����д�жϷ�����
*/

//��ʱ����
void Delay(uint32_t count )
{
	for(; count!=0; count--);
}

int main(void)
{	
	//uint8_t i =0;
	//uint8_t a[10] = {1,2,3,4,5,6,7,8,9,10};
	uint8_t ch = 0;//���յ��Է�����Ƭ��������
	USART_Config();
	//LED_GPIO_Config();
	
	//Usart_SendByte(DEBUG_USARTx,0x64);
	//Usart_SendWord(DEBUG_USARTx,0xff56);
	
	//Usart_SendArray(DEBUG_USARTx,a,10);
	 //Usart_SendStr(DEBUG_USARTx,"����ͨ��ѧϰ����");
	
	//printf�������ǿ�������λ������ʾ�ģ�����ͷ��������
	/*
	printf("����printf��������\n");
	for(i = 0; i < 10;i++)
	{
		printf("%d\n",a[i]);
	}
	*/
	printf("����һ�����ڿ���RGB�Ƶĳ���\n");
	
//	while(1)
//	{
//		ch = getchar();
//		printf("ch = %c\n",ch);
//		
//		switch(ch)
//		{
//			case '1':LED_RED;
//			break;
//			
//			default:LED_RGBOFF;
//			break;
//		}
//	}

	while (1)
	{
		ch = getchar();
	    printf( "ch=%c\n",ch );
		
		if(ch != 0) printf("����ִ�е�������\n");
		switch(ch)
		{
			case '1': 
				LED_RED;
				printf("��鵽�����%c\n",ch);	
				break;
		 
			case '2': 
				LED_GREEN;
				printf("��鵽�����%c\n",ch);	
			  break;
		 
			case '3': LED_BLUE;
				printf("��鵽�����%c\n",ch);	
			  break;
		 
			default: 
				LED_RGBOFF;
				printf("δ����1-3֮����ַ�\n");
				
		    break;
		 }
	}
	
}



