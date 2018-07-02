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

/** \ingroup    CMSIS_core_register
    \defgroup   CMSIS_NVIC  Nested Vectored Interrupt Controller (NVIC)
    \brief      Type definitions for the NVIC Registers
  @{
 */

/** \brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
typedef struct
{
  __IO uint32_t ISER[8];                 /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register           */
       uint32_t RESERVED0[24];
  __IO uint32_t ICER[8];                 /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register         */
       uint32_t RSERVED1[24];
  __IO uint32_t ISPR[8];                 /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register          */
       uint32_t RESERVED2[24];
  __IO uint32_t ICPR[8];                 /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register        */
       uint32_t RESERVED3[24];
  __IO uint32_t IABR[8];                 /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register           */
       uint32_t RESERVED4[56];
  __IO uint8_t  IP[240];                 /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
       uint32_t RESERVED5[644];
  __IO uint32_t STIR;                    /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register     */
}  NVIC_TypeDef;