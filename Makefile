ARMGNU ?= arm-none-eabi
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding

COMMON = $(ROOT)common/common.o $(ROOT)common/gpio.o $(ROOT)common/wait.o $(ROOT)common/periph.o
all : $(DEST)

clean :
	rm -f ./*.o
	rm -f ./*.list
	rm -f ./*.elf
	rm -f ./*.img

$(DEST): $(COMMON) $(NAME).elf
	$(ARMGNU)-objcopy $(NAME).elf -O binary $(DEST)

$(NAME).elf: $(OBJECTS)
	$(ARMGNU)-ld $^ $(patsubst %, $(ROOT)common/%, $(LINK)) -T $(MMAP) -o $@
	$(ARMGNU)-objdump -D $(NAME).elf > $(NAME).list

%.o: %.c
	$(ARMGNU)-gcc $(COPS) -c $< -o $@

%.o: %.s
	$(ARMGNU)-as -c $< -o $@
