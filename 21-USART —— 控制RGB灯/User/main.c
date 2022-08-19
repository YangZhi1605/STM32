#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_usart.h"


//#define SOFT_DELAY Delay(0xFFFFF);
/*
1、初始化串口需要用到的GPIO
2、初始化串口，USART_InitTypeDef
3、中断配置(接收中断，中断优先级)
4、使能串口
5、编写发送和接收函数
6、编写中断服务函数
*/

//延时函数
void Delay(uint32_t count )
{
	for(; count!=0; count--);
}

int main(void)
{	
	//uint8_t i =0;
	//uint8_t a[10] = {1,2,3,4,5,6,7,8,9,10};
	uint8_t ch = 0;//接收电脑发给单片机的数据
	USART_Config();
	//LED_GPIO_Config();
	
	//Usart_SendByte(DEBUG_USARTx,0x64);
	//Usart_SendWord(DEBUG_USARTx,0xff56);
	
	//Usart_SendArray(DEBUG_USARTx,a,10);
	 //Usart_SendStr(DEBUG_USARTx,"串口通信学习测试");
	
	//printf的内容是可以在上位机中显示的，这个就方便调试了
	/*
	printf("串口printf函数测试\n");
	for(i = 0; i < 10;i++)
	{
		printf("%d\n",a[i]);
	}
	*/
	printf("这是一个串口控制RGB灯的程序\n");
	
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
		
		if(ch != 0) printf("程序执行到这里了\n");
		switch(ch)
		{
			case '1': 
				LED_RED;
				printf("检查到输入的%c\n",ch);	
				break;
		 
			case '2': 
				LED_GREEN;
				printf("检查到输入的%c\n",ch);	
			  break;
		 
			case '3': LED_BLUE;
				printf("检查到输入的%c\n",ch);	
			  break;
		 
			default: 
				LED_RGBOFF;
				printf("未输入1-3之间的字符\n");
				
		    break;
		 }
	}
	
}



