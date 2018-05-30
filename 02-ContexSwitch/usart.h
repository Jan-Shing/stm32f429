#include<stdint.h>

#define  USART_CR1_OVER8                     ((uint16_t)0x8000)            /*!<USART Oversampling by 8 enable         */
#


/** @ USART_Word_Length
  * @{
 */

 #define USART_WordLength_8b			           ((uint16_t)0x0000)
 #define USART_WordLength_9b				         ((uint16_t)0x1000)
/**
  * @}
  */

/** @ USART_Parity_Control
  *
 */
#define USART_Parity_None				           	((uint16_t)0x0000)
#define USART_Parity_Even 			         		((uint16_t)0x0040)
#define USART_Parity_Odd 				           	((uint16_t)0x0060)
/**
  * @}
  */

/** @ USART_Word_Mode
  *
 */
#define USART_Mode_RX					        	   ((uint16_t)0x0004)
#define USART_Mode_TX				         		   ((uint16_t)0x0008)
#define USART_Mode_ENR                     ((uint16_t)0x2000)
/**
  * @}
  */

/** @ USART_Stop_Bits
  *
 */
 #define USART_StopBits_1			        		((uint16_t)0x0000)
 #define USART_StopBits_0_5		         		((uint16_t)0x1000)
 #define USART_StopBits_2			        		((uint16_t)0x2000)
 #define USART_StopBits_1_5		         		((uint16_t)0x3000)
/**
  * @}
  */




