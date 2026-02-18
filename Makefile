CFLAGS := -o out.elf -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Wall -Wextra -Werror -g -Og
CSOURCES := ./main.c ./syscalls.c ./uart.c ./CMSIS/Device/Source/system_stm32f4xx.c 
CINCLUDE := -I./CMSIS/Core/Include -I./CMSIS/Core/Include/m-profile -I./CMSIS/Device/Include
OUTPUT := -o out.elf

GCC := arm-none-eabi-gcc
GCCCSOURCES := ./CMSIS/Device/Source/startup_stm32f411xe.s
GCCLINK := -T ./linkerscript_gcc.ld
GCCFLAGS:= -specs=nano.specs

CLANG := clang
CLANGCSOURCES := ./clang_init.c ./clang_startup.c
CLANGLINK := -T ./linkerscript_clang.ld
CLANGFLAGS := --target=arm-none-eabi

main:
	$(GCC) $(CSOURCES) $(GCCCSOURCES) $(GCCLINK) $(CFLAGS) $(GCCFLAGS) $(CINCLUDE) $(OUTPUT)

clang:
	$(CLANG) $(CSOURCES) $(CLANGCSOURCES) $(CLANGLINK) $(CFLAGS) $(CLANGFLAGS) $(CINCLUDE) $(OUTPUT)

.PHONY: clean flash

clean: 
	-del *.elf 
	-del *.bin 
	-del *.hex

flash: 
	pyocd load out.elf