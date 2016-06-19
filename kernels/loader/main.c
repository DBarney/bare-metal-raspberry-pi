#include "../../common/common.h"
#include "../../common/uart.h"
#include "../../common/wait.h"

//-------------------------------------------------------------------------

int kmain ( void )
{
    init();
    uart_print("\r\n\r\n");
    uart_print("####################################\r\n");
    uart_print("WELCOME TO THE SERIAL BOOT LOADER\r\n");
    uart_print("WRITTEN BY DANIEL BARNEY\r\n");
    uart_print("####################################\r\n");
again:
    uart_print("waiting for kernel to be sent...\r\n");

    int size = uart_recv();
    size += uart_recv() << 8;
    size += uart_recv() << 16;
    size += uart_recv() << 24;

    if (size == 0) {
      uart_print("n -- kernel must have a size");
      goto again;
    }
    if (size > 0x200000 - 0x8000) {
      uart_print("n");
      busy_wait(0x100000);
      uart_print(" -- kernel is too large\r\n");
      uart_hexstring(size);
      goto again;
    }

    //inform load to send the kernel
    uart_print("y");

    //load the new kernel into ram
    uart_print("loading kernel...\r\n");
    char *kernel = (char*)0x8000;
    while(size-- > 0) {
    	*kernel++ = uart_recv();
    }
    busy_wait(0x100000);
    uart_print("booting kernel\r\n");
    asm("bl 0x8000");
    uart_print("halting\r\n");
    return(0);
}
