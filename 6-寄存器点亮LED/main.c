#include "stm32f10x.h"

int main(void){
	
	//开启GPIOB 的端口始终（在3的位置）
	RCC_APB2ENR |= (1<<3);
	
	//清空控制PB0的端口位
	GPIOB_CRL &= ~(0x0F <<(4*0));
	//配置PB0为通用推挽输出，速度是10M
	GPIOB_CRL |= (1 << 4*0);
	
	//PB0 输出低电平
	GPIOB_ODR |= (0<<0);
	
	while(1);
}


/*
Reset_Handler 调用了该函数用来初始化 SMT32 系统时钟，
为了简单起见，我们在 main 文件里面定义一个 SystemInit 空函数
目的是为了骗过编译器不报错
*/
void SystemInit(void){
	
}
