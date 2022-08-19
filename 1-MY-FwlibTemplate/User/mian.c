#include "stm32f10x.h"  //相当于51单片机中，#include <reg51.h>

void Delay(uint32_t count)
{
	for(;count != 0; count--);
}

int main()
{
    //来到这里的时候，系统时钟已经被配置成为了72M
	
}
