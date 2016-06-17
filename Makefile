ARMGNU ?= arm-none-eabi
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding

all : echo.bin loader.bin load

clean :
	rm -f *.o
	rm -f kernels/echo/main.o
	rm -f kernels/loader/main.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc
	rm -f *.clang.opt.s

vectors.o : vectors.s
	$(ARMGNU)-as vectors.s -o vectors.o

vectors_loader.o : vectors_loader.s
	$(ARMGNU)-as vectors_loader.s -o vectors_loader.o

periph.o : common/periph.c common/common.h
	$(ARMGNU)-gcc $(COPS) -c common/periph.c -o periph.o

common.o : common/common.c common/common.h
		$(ARMGNU)-gcc $(COPS) -c common/common.c -o common.o


load: load.c
	gcc load.c -o load

kernels/echo/main.o : kernels/echo/main.c
	$(ARMGNU)-gcc $(COPS) -c kernels/echo/main.c -o kernels/echo/main.o

echo.elf : kernels/echo/memmap vectors.o kernels/echo/main.o common.o periph.o
	$(ARMGNU)-ld vectors.o kernels/echo/main.o common.o periph.o -T kernels/echo/memmap -o echo.elf
	$(ARMGNU)-objdump -D echo.elf > echo.list

echo.bin : echo.elf
	$(ARMGNU)-objcopy echo.elf -O binary echo.bin


kernels/loader/main.o : kernels/loader/main.c
	$(ARMGNU)-gcc $(COPS) -c kernels/loader/main.c -o kernels/loader/main.o

loader.elf : kernels/loader/memmap vectors_loader.o kernels/loader/main.o common.o periph.o
	$(ARMGNU)-ld vectors_loader.o kernels/loader/main.o common.o periph.o -T kernels/loader/memmap -o loader.elf
	$(ARMGNU)-objdump -D loader.elf > loader.list

loader.bin : loader.elf
	$(ARMGNU)-objcopy loader.elf -O binary loader.bin
