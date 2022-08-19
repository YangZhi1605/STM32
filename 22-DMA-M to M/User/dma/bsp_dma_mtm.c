#include "bsp_dma_mtm.h"


/* 定义aSRC_Const_Buffer数组作为DMA传输数据源
 * const关键字将aSRC_Const_Buffer数组变量定义为常量类型
 * 表示数据存储在内部的FLASH中
 */
 //DST（destination：目的地）、SRC(source:源、信息源、源点)src
const uint32_t aSRC_Const_Buffer[BUFFER_SIZE]= {
                                    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
                                    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
                                    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
                                    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
                                    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
                                    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
                                    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
                                    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80};
/* 定义DMA传输目标存储器
 * 存储在内部的SRAM中		 //SRAM（静态随机存取存储器)																
 */ 
//dst 外设
uint32_t aDST_Buffer[BUFFER_SIZE];
									
							
//typedef struct
//{
//  uint32_t DMA_PeripheralBaseAddr;   // 外设地址
//  uint32_t DMA_MemoryBaseAddr;       // 存储器地址
//  uint32_t DMA_DIR;                  // 传输方向
//  uint32_t DMA_BufferSize;           // 传输数目
//  uint32_t DMA_PeripheralInc;        // 外设地址增量模式
//  uint32_t DMA_MemoryInc;            // 存储器地址增量模式
//  uint32_t DMA_PeripheralDataSize;   // 外设数据宽度
//  uint32_t DMA_MemoryDataSize;       // 存储器数据宽度
//  uint32_t DMA_Mode;                 // 模式选择
//  uint32_t DMA_Priority;             // 通道优先级
//  uint32_t DMA_M2M;                  // 存储器到存储器模式
//}DMA_InitTypeDef;
									
void MtM_DMA_Config(void)
{
	//利用该外设的库函数中提供的结构体进行初始化
	DMA_InitTypeDef DMA_InitStruct;
	
	//STM32 中使用任何设备的核心，是开时钟，时钟就像是他们的心脏，要通过一些系统构架图
	//找到自己正要使用的外设挂载的时钟总线，然后再到rcc.h中找，对于DMA，其挂载的总线是AHB系统总线
	RCC_AHBPeriphClockCmd(MTM_DMA_CLK,ENABLE);//第一个参数一般是具体的硬件端口，推荐宏定义，方便移植，第二个参数一般都是ENABLE使能
	
	//下面就是具体的设定声明的结构体的参数了，然后通过Init库函数，完成参数加载到寄存器
	
	/*一、数据从哪里来，到哪里去*/
	//确定外设基本地址 —— 相当于指定数据源头，本项目中是上面的数组
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)aSRC_Const_Buffer;
	//确定存储器基本地址 —— 相当于指定数据最终存的位置
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)aDST_Buffer;
	//确定传送方向 —— 数据从源中发出，所以应该是选SRC
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC  ;
	
	
	/*二、数据要传输多少，传的单位是什么*/
	//确定传输数目
	DMA_InitStruct.DMA_BufferSize = BUFFER_SIZE;
	//确定外设地址是增量模式与否，这里按照其头文件里写的，就enable和disable了
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	//确定外设数据的宽度
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;//其实我不懂为什么是按照字，确实应该切合32位，但是1word = 2byte=16bit 位。先考虑能跑吧，后面抓细节
	//好了，我懂了，确实，上面给的传送数目是32 DMA_PeripheralDataSize_Word        ((uint32_t)0x00000200)
	//这玩意，写的是Word，其实按照16进制翻译过来，就是32
	//确定存储器地址是否为增量模式
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//确定存储器的数据宽度
	DMA_InitStruct.DMA_MemoryDataSize= DMA_MemoryDataSize_Word;
	
	
	/*三、什么时候结束传输*/
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Enable;
	
	//调用库函数完成初始化
	//和硬件相关的，都定义为宏
	//DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct);
	DMA_Init(MTM_DMA_CHANNEL,&DMA_InitStruct);
	
	DMA_ClearFlag(MTM_DMA_FLAG_TC);//不是特别必要
	//使能这个DMA
	//DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState);
	DMA_Cmd(MTM_DMA_CHANNEL,ENABLE);
}

/**
  * 比较函数
  * 判断指定长度的两个数据源是否完全相等，
  * 如果完全相等返回1，只要其中一对数据不相等返回0
  */
uint8_t Buffercmp(const uint32_t* pBuffer, 
                  uint32_t* pBuffer1, uint16_t BufferLength)
{
  /* 数据长度递减 */
  while(BufferLength--)
  {
    /* 判断两个数据源是否对应相等 */
    if(*pBuffer != *pBuffer1)
    {
      /* 对应数据源不相等马上退出函数，并返回0 */
      return 0;
    }
    /* 递增两个数据源的地址指针 */
    pBuffer++;
    pBuffer1++;
  }
  /* 完成判断并且对应数据相对 */
  return 1;  
}