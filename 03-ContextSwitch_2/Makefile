CROSS_COMPILE ?= arm-none-eabi-
AS := $(CROSS_COMPILE)as
# Cortex-M4 implements the ARMv7E-M arch
CPU = cortex-m4
CFLAGS = -mcpu=$(CPU) -march=armv7e-m -mtune=cortex-m4
CFLAGS += -mlittle-endian -mthumb
# Basic configurations
CFLAGS += -g -std=c99
CFLAGS += -Wall
# specify STM32F429
CFLAGS += -DSTM32F429_439xx
# Link
CFLAGS += -T simple.ld -nostartfiles


TARGET = OS.bin
all: $(TARGET)

$(TARGET): os.c startup.c context_switch.S syscall.S
	$(CROSS_COMPILE)gcc $(CFLAGS) $^ -o OS.out
	$(CROSS_COMPILE)objcopy -Obinary OS.out OS.bin
	$(CROSS_COMPILE)objdump -S OS.out > OS.list

clean:
	rm -rf *.o *.out *.bin
flash:
	../../st-flash write OS.bin 0x8000000
openocd_flash:
	openocd -f interface/stlink-v2.cfg \
		-f target/stm32f4x_stlink.cfg \
		-c "init" \
		-c "reset init" \
		-c "stm32f2x unlock 0" \
		-c "flash probe 0" \
		-c "flash info 0" \
		-c "flash write_image erase blink.bin 0x8000000" \
		-c "reset run" -c shutdown || \
		../st-flash write blink.bin 0x8000000
