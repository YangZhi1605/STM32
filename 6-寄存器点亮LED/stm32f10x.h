

/*本文件用于添加寄存器地址及结构体定义*/

/*片上外设基地址  */
#define PERIPH_BASE           ((unsigned int)0x40000000)

/*APB2 总线基地址 */
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
/* AHB总线基地址 */
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)

/*GPIOB外设基地址*/
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x0C00)

/* GPIOB寄存器地址,强制转换成指针 */
#define GPIOB_CRL			*(unsigned int*)(GPIOB_BASE+0x00)//GPIO端口配置低寄存器
#define GPIOB_CRH			*(unsigned int*)(GPIOB_BASE+0x04)//GPIO端口配置高寄存器
#define GPIOB_IDR			*(unsigned int*)(GPIOB_BASE+0x08)//GPIO数据输入寄存器
#define GPIOB_ODR			*(unsigned int*)(GPIOB_BASE+0x0C)//GPIO数据输出寄存器
#define GPIOB_BSRR	  *(unsigned int*)(GPIOB_BASE+0x10)//GPIO位设置/清除寄存器
#define GPIOB_BRR			*(unsigned int*)(GPIOB_BASE+0x14)//GPIO端口为清除寄存器
#define GPIOB_LCKR		*(unsigned int*)(GPIOB_BASE+0x18)//GPIO端口配置锁定寄存器

/*RCC外设基地址*/
#define RCC_BASE      (AHBPERIPH_BASE + 0x1000)
/*RCC的AHB1时钟使能寄存器地址,强制转换成指针*/
#define RCC_APB2ENR		 *(unsigned int*)(RCC_BASE+0x18)

