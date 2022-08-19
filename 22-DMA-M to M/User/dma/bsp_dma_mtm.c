#include "bsp_dma_mtm.h"


/* ����aSRC_Const_Buffer������ΪDMA��������Դ
 * const�ؼ��ֽ�aSRC_Const_Buffer�����������Ϊ��������
 * ��ʾ���ݴ洢���ڲ���FLASH��
 */
 //DST��destination��Ŀ�ĵأ���SRC(source:Դ����ϢԴ��Դ��)src
const uint32_t aSRC_Const_Buffer[BUFFER_SIZE]= {
                                    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
                                    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
                                    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
                                    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
                                    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
                                    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
                                    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
                                    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80};
/* ����DMA����Ŀ��洢��
 * �洢���ڲ���SRAM��		 //SRAM����̬�����ȡ�洢��)																
 */ 
//dst ����
uint32_t aDST_Buffer[BUFFER_SIZE];
									
							
//typedef struct
//{
//  uint32_t DMA_PeripheralBaseAddr;   // �����ַ
//  uint32_t DMA_MemoryBaseAddr;       // �洢����ַ
//  uint32_t DMA_DIR;                  // ���䷽��
//  uint32_t DMA_BufferSize;           // ������Ŀ
//  uint32_t DMA_PeripheralInc;        // �����ַ����ģʽ
//  uint32_t DMA_MemoryInc;            // �洢����ַ����ģʽ
//  uint32_t DMA_PeripheralDataSize;   // �������ݿ��
//  uint32_t DMA_MemoryDataSize;       // �洢�����ݿ��
//  uint32_t DMA_Mode;                 // ģʽѡ��
//  uint32_t DMA_Priority;             // ͨ�����ȼ�
//  uint32_t DMA_M2M;                  // �洢�����洢��ģʽ
//}DMA_InitTypeDef;
									
void MtM_DMA_Config(void)
{
	//���ø�����Ŀ⺯�����ṩ�Ľṹ����г�ʼ��
	DMA_InitTypeDef DMA_InitStruct;
	
	//STM32 ��ʹ���κ��豸�ĺ��ģ��ǿ�ʱ�ӣ�ʱ�Ӿ��������ǵ����࣬Ҫͨ��һЩϵͳ����ͼ
	//�ҵ��Լ���Ҫʹ�õ�������ص�ʱ�����ߣ�Ȼ���ٵ�rcc.h���ң�����DMA������ص�������AHBϵͳ����
	RCC_AHBPeriphClockCmd(MTM_DMA_CLK,ENABLE);//��һ������һ���Ǿ����Ӳ���˿ڣ��Ƽ��궨�壬������ֲ���ڶ�������һ�㶼��ENABLEʹ��
	
	//������Ǿ�����趨�����Ľṹ��Ĳ����ˣ�Ȼ��ͨ��Init�⺯������ɲ������ص��Ĵ���
	
	/*һ�����ݴ���������������ȥ*/
	//ȷ�����������ַ ���� �൱��ָ������Դͷ������Ŀ�������������
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)aSRC_Const_Buffer;
	//ȷ���洢��������ַ ���� �൱��ָ���������մ��λ��
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)aDST_Buffer;
	//ȷ�����ͷ��� ���� ���ݴ�Դ�з���������Ӧ����ѡSRC
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC  ;
	
	
	/*��������Ҫ������٣����ĵ�λ��ʲô*/
	//ȷ��������Ŀ
	DMA_InitStruct.DMA_BufferSize = BUFFER_SIZE;
	//ȷ�������ַ������ģʽ������ﰴ����ͷ�ļ���д�ģ���enable��disable��
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	//ȷ���������ݵĿ��
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;//��ʵ�Ҳ���Ϊʲô�ǰ����֣�ȷʵӦ���к�32λ������1word = 2byte=16bit λ���ȿ������ܰɣ�����ץϸ��
	//���ˣ��Ҷ��ˣ�ȷʵ��������Ĵ�����Ŀ��32 DMA_PeripheralDataSize_Word        ((uint32_t)0x00000200)
	//�����⣬д����Word����ʵ����16���Ʒ������������32
	//ȷ���洢����ַ�Ƿ�Ϊ����ģʽ
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//ȷ���洢�������ݿ��
	DMA_InitStruct.DMA_MemoryDataSize= DMA_MemoryDataSize_Word;
	
	
	/*����ʲôʱ���������*/
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Enable;
	
	//���ÿ⺯����ɳ�ʼ��
	//��Ӳ����صģ�������Ϊ��
	//DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct);
	DMA_Init(MTM_DMA_CHANNEL,&DMA_InitStruct);
	
	DMA_ClearFlag(MTM_DMA_FLAG_TC);//�����ر��Ҫ
	//ʹ�����DMA
	//DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState);
	DMA_Cmd(MTM_DMA_CHANNEL,ENABLE);
}

/**
  * �ȽϺ���
  * �ж�ָ�����ȵ���������Դ�Ƿ���ȫ��ȣ�
  * �����ȫ��ȷ���1��ֻҪ����һ�����ݲ���ȷ���0
  */
uint8_t Buffercmp(const uint32_t* pBuffer, 
                  uint32_t* pBuffer1, uint16_t BufferLength)
{
  /* ���ݳ��ȵݼ� */
  while(BufferLength--)
  {
    /* �ж���������Դ�Ƿ��Ӧ��� */
    if(*pBuffer != *pBuffer1)
    {
      /* ��Ӧ����Դ����������˳�������������0 */
      return 0;
    }
    /* ������������Դ�ĵ�ַָ�� */
    pBuffer++;
    pBuffer1++;
  }
  /* ����жϲ��Ҷ�Ӧ������� */
  return 1;  
}