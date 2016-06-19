ARMGNU ?= arm-none-eabi
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding

LIBS = $(patsubst %, $(ROOT)common/%, $(LINK))
all : $(DEST)

clean :
	rm -f ./*.o
	rm -f ./*.list
	rm -f ./*.elf
	rm -f ./*.img

$(DEST): $(NAME).elf
	$(ARMGNU)-objcopy $(NAME).elf -O binary $(DEST)

$(NAME).elf: $(OBJECTS) $(LIBS)
	$(ARMGNU)-ld $^ -T $(MMAP) -o $@
	$(ARMGNU)-objdump -D $(NAME).elf > $(NAME).list

%.o: %.c
	$(ARMGNU)-gcc $(COPS) -c $< -o $@

%.o: %.s
	$(ARMGNU)-as -c $< -o $@
