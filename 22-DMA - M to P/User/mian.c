#include "stm32f10x.h"  //相当于51单片机中，#include <reg51.h>
#include "bsp_led.h"
#include "bsp_usart_dma.h"


extern uint8_t SendBuff[SENDBUFF_SIZE];

void Delay(uint32_t count)
{
	for(;count !=0; count--);
}

//3-编写主函数（开启串口发送DMA请求）。
int main()
{
	uint16_t i;
	LED_GPIO_Config();
	USART_Config();
	
	//填充数据
	for(i = 0;i <SENDBUFF_SIZE;i++)
	{
		SendBuff[i] = 'P';
	}
	
	//配置DMA
	USARTx_DMA_Config();
	//请求发送
	//void USART_DMACmd(USART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState); 串口使能DMA请求
	USART_DMACmd(DEBUG_USARTx,USART_DMAReq_Tx,ENABLE);
	
	while(1)
	{
		LEDR_TOGGLE
		Delay(0xFFFFFF); 
		
	}
}

