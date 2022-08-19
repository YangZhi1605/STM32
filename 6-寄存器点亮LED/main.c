#include "stm32f10x.h"

int main(void){
	
	//����GPIOB �Ķ˿�ʼ�գ���3��λ�ã�
	RCC_APB2ENR |= (1<<3);
	
	//��տ���PB0�Ķ˿�λ
	GPIOB_CRL &= ~(0x0F <<(4*0));
	//����PB0Ϊͨ������������ٶ���10M
	GPIOB_CRL |= (1 << 4*0);
	
	//PB0 ����͵�ƽ
	GPIOB_ODR |= (0<<0);
	
	while(1);
}


/*
Reset_Handler �����˸ú���������ʼ�� SMT32 ϵͳʱ�ӣ�
Ϊ�˼������������ main �ļ����涨��һ�� SystemInit �պ���
Ŀ����Ϊ��ƭ��������������
*/
void SystemInit(void){
	
}
