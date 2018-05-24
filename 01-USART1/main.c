#include <stdint.h>
#include "reg.h"
#include "usart.h"

#define HSI_VALUE    ((uint32_t)16000000) /*!< Value of the Internal oscillator in Hz, which is system default and after reset clock freq*/

#define USART1 			((USART_TypeDef *) 	0x40011000)
/*  Data is transferred to the shift register*/
#define USART_FLAG_TXE 	((uint16_t) 0x0080)      

static char greet[] = "Hello memory world!";
/*Initialize the USART1*/
void init_usart(USART_TypeDef * USARTx, uint32_t baud_rate)
{
	uint32_t temp_reg = 0x00, apbclock = 0x00;
	uint32_t integer_divider = 0x00;	
	uint32_t fraction_divider = 0x00;	
/*-------------------USART CR2 Configuration---------------------------*/
	temp_reg = USARTx->CR2;
	
	/* Confgure the USART stop bits*/
	temp_reg |= USART_StopBits_1;

	USARTx->CR2 = temp_reg;
/*-------------------USART CR1 Cionfiguration---------------------------*/
	temp_reg = USARTx->CR1;
	/* Configure the USART Word Length, Parity and mode: 
	    Set the M bits according to USART_WordLength value 
		Set PCE and PS bits according to USART_Parity value
		Set TE and RE bits according to USART_Mode value */
	temp_reg |= USART_WordLength_8b | USART_Parity_None \
				| USART_Mode_TX | USART_Mode_RX | USART_Mode_ENR;
				
	/*Write to USART CR1*/
	USARTx->CR1 = temp_reg;
	
/*-------------------USART BRR Configuration---------------------------*/
	apbclock = HSI_VALUE;
		
	/* Signal oversampled*/
	if (USARTx->CR1 & USART_CR1_OVER8)
		/* Integer part computing in case Oversampling mode is 8 samples*/
		integer_divider = ((25 * apbclock) / (2 *  baud_rate));
	else
		integer_divider = ((25 * apbclock) / (4 *  baud_rate));
	temp_reg = (integer_divider / 100 ) << 4;

	/* Computing fraction part*/
	fraction_divider = integer_divider - (100 * (temp_reg >> 4));
	/* Implement fraction part to register, which represent
		how much 1/8 or 1/16                                */
	if (USARTx->CR1 & USART_CR1_OVER8)
		temp_reg |= ((((fraction_divider * 8) + 50)) / 100) & ((uint8_t)0x07);	
	else
		temp_reg |= ((((fraction_divider * 16) + 50)) / 100) & ((uint8_t)0x0F);

	/* write to USART BRR register */
	USARTx->BRR = (uint16_t)temp_reg;



}

void putstr(const char *str)
{
	while(*str){
		while(!(USART1->SR & USART_FLAG_TXE));
			USART1->DR = *str & 0xFF;
			 str++;
	}

}


int main (void){
 
	/* Enable GPIO piort A  Clock*/
	*RCC_AHB1ENR |= 0x01;
	/*	Enable USART 2 clock*/
 	*RCC_APB2ENR |= RCC_APB2ENR_USART1;
	/* Clear mode bits for pin9 and pin10*/
	*GPIOA_MODER &= ~(0xF << (2*9));
	/* Select Alternate function mode for pin9 and pin10*/
	*GPIOA_MODER |= (0xA << (2*9));
	/* Alternative function 7 for USART2, set for pin9 and pin10*/
	*GPIOA_ALTERNATE_FUNCTION_H |= 0x77 << 4;
	/* GPIO Speed*/
	*GPIOA_OUTPUT_SPEED |= 0x0F << ( 2 * 9);
	/* GPIO Push Pull */
	*GPIOA_PUPDR &= ~(0xF <<(2 * 9));
	*GPIOA_PUPDR |= 0x05 << (2 * 9);

	init_usart(USART1, 9600);

	putstr(greet);


}
