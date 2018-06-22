#include <stdint.h>
#include <stddef.h> 		/* for size_t*/
#include "reg.h"
#include "usart.h"
#include "asm.h"

#define HSI_VALUE    ((uint32_t)16000000) /*!< Value of the Internal oscillator in Hz, which is system default and after reset clock freq*/

#define USART1 			((USART_TypeDef *) 	0x40011000)
/*  Data is transferred to the shift register*/
#define USART_FLAG_TXE 	((uint16_t) 0x0080)      

static char greet[] = "OS Starting...\n";
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
/* Exception return behavior */
#define HANDLER_MSP	0xFFFFFFF1
#define THREAD_MSP	0xFFFFFFF9
#define THREAD_PSP	0xFFFFFFFD

/* Size of our user task stacks in words */
#define STACK_SIZE 256
/* Number of user task */
#define TASK_LIMIT 2
/* Initialize user task stack and execute it one time .
 * We set "THREAD_PSP" to LR so that exception return
 * works correctly.
*/

unsigned int *create_task(unsigned int *stack, void (*start)(void))
{
	static int first = 1;
	stack += STACK_SIZE - 17; /* End of stack, minus what we are about to push*/
	/* For Unknown reason, cortex-M4 can't use Except_return 
	 * At first time, so workaround by using control register
	 * at first time.
	*/

	if (first){
		stack[8] = (unsigned int)start;
		first = 0;
		stack = init(stack);
	}else{
		stack[8] = (unsigned int)THREAD_PSP;   /* PoP to LR*/
		stack[15] = (unsigned int)start;	   /* unstaking to PC*/
		stack[16] = (unsigned int) 0x01000000; /* PSR Thumb bit*/
		stack = activate(stack);
	}
	putstr("activate task");
	putstr("before return stack");

	return stack;
}
void task1_func(void)
{
	static char count_fun1 = '0';
	char msg[10] = "EXE: 0";
	
	putstr("Task1: Created!\n");
	syscall();
	while(1){
		count_fun1++;
		msg[5] = count_fun1;
		putstr(msg);
		putstr("Task1: Executed@\n");
		syscall();
	}
}

void task2_func(void)
{
	static char count_fun2 = '0';
	char msg[10] = "EXE: 0";

	putstr("Task2: Created!\n");
	syscall();
	while(1){
		count_fun2++;
		msg[5] = count_fun2;
		putstr(msg);
		putstr("Task2: Executed@\n");
		syscall();
	}
}

int main (void)
{
 
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


	/* Initialization of process stack. */
	unsigned int user_stacks[TASK_LIMIT][STACK_SIZE];
	unsigned int *usertasks[TASK_LIMIT];
	size_t task_count = 0;
	size_t current_task;
	
	putstr(greet);
	
	putstr("OS: Create the first user task\n");
	usertasks[0] = create_task(user_stacks[0], &task1_func);
	task_count++;

	putstr("OS: Return to the OS mode, create task 2!\n");
	usertasks[1] = create_task(user_stacks[1], &task2_func);
	task_count++;

	putstr("OS: Start Multitasking\n");
	current_task = 0;

	int i = 0;
	while(i++ < 10){
		putstr("OS: Activate next task\n");
		usertasks[current_task] = activate(usertasks[current_task]);
		putstr("OS: Back to OS\n");

		task_count++;
		current_task = task_count % TASK_LIMIT;
	}

}
