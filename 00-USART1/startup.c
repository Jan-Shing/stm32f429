#include <stdint.h>

extern void main (void);

void reset_handler(void)
{
	main();
}

__attribute((section(".isr_vector")))
uint32_t *isr_vectors[] = {
	(uint32_t * )0x20010000,
	(uint32_t *) reset_handler,
};
