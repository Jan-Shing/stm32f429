ENTRY(reset_handler)

MEMORY
{
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1024k
	RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 192k

}

SECTIONS 
{
	.text :
	{
		KEEP(*(.isr_vector))
		*(.text)
		*(.text.*)
		*(.rodata)
		_sromdev = .;               /* .rom.xxx  section start address */
		_eromdev = .;				/* .rom.xxx  section  end address */
		_sidata = .;               /*	.data section start address*/
	} >FLASH
	/* Initialized data will initially be  loaded in Flash at the end of .text section*/
	.data : AT(_sidata)
	{
		_sdata = .;
		*(.data)                    /* Initialized data*/
		*(.data*)
		_edata = .;
	} >RAM
	/* Zero-filled run time allocate data memory */
	.bss :
	{
		_sbss = .;
		*(.bss)
		_ebss = .;
	} >RAM
	
	/* Place the stack pointer at top end of RAM*/
	_estack = ORIGIN(RAM) + LENGTH(RAM); 
}
