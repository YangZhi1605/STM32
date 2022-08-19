#include "stm32f10x.h"  //相当于51单片机中，#include <reg51.h>
#include "bsp_led.h"
#include "bsp_dma_mtm.h"

/*
编程要点 —— 主要是阐述步骤，至于具体的代码，他都是移植的，去理解逻辑吧

1、在FLASH中定义好要传送的数据，在SRAM汇总定义好用来接受FLASH数据的变量
2、初始化DMA，主要配置DMA初始化结构体
3、编写比较函数
4、编写main函数

*/
extern const uint32_t aSRC_Const_Buffer[BUFFER_SIZE];
extern uint32_t aDST_Buffer[BUFFER_SIZE];

void Delay(uint32_t count)
{
	for(;count !=0; count--);
}

int main()
{
	uint8_t status = 0;
	LED_GPIO_Config();
	LED_YELLOW;//黄灯起步
	Delay(0xFFFFFF);
	
	MtM_DMA_Config();
	
	while(DMA_GetFlagStatus(MTM_DMA_FLAG_TC ) == RESET );//用这个函数 + while 检测数据传送是否完成，在传送完成的情况下，进行下一步，防止CPU过快
	
	status =  Buffercmp(aSRC_Const_Buffer, aDST_Buffer, BUFFER_SIZE);
	
	if( status == 0 )
	{
		//不一样的话，亮红灯
		LED_RED;
	}else{
		//一样的话，亮绿灯
		LED_GREEN;
		
	}

  while(1)
  {
	  
  }
	
}

