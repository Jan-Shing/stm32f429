#include<stdint.h>
#define __IO volatile
#define __REG  __IO uint32_t *

#define RCC_APB2ENR_USART1                   	 ((uint32_t)0x00000010)
#define GPIOA_BASE                          	 ((uint32_t)0x40020000)
#define GPIOA_MODER							     ((__REG)(GPIOA_BASE + 0x0 ))
#define GPIOA_PUPDR                         	 ((__REG)(GPIOA_BASE + 0x0C))
#define GPIOA_ALTERNATE_FUNCTION_L			     ((__REG)(GPIOA_BASE + 0x20))
#define GPIOA_ALTERNATE_FUNCTION_H			     ((__REG)(GPIOA_BASE + 0x24))
#define GPIOA_OUTPUT_SPEED                    	 ((__REG)(GPIOA_BASE + 0x08))

#define RCC_CLOCK_BASE                       	 ((uint32_t)0x40023800)
#define RCC_AHB1ENR                           	 ((__REG) (RCC_CLOCK_BASE + 0x30))
#define RCC_APB2ENR                           	 ((__REG) (RCC_CLOCK_BASE + 0x44))

typedef struct {
	__IO uint32_t SR;   //0x0
	__IO uint32_t DR;   //0x04
	__IO uint32_t BRR;  //0x08
	__IO uint32_t CR1;  //0x0c
	__IO uint32_t CR2;  //0x10
	__IO uint32_t CR3;  //0x14
	__IO uint32_t GTPR; //0x18
} USART_TypeDef;

typedef struct {
	__IO uint32_t CTRL;
	__IO uint32_t LOAD; //0x04
	__IO uint32_t VAL;
	__IO uint32_t CALB; //0x0C
} SYSTICK_TypeDef;
