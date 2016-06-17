#include "../../common/common.h"

//-------------------------------------------------------------------------

typedef void (*entry_fn)();

int kmain ( void )
{
    init();
    print("\r\n\r\n");
    print("####################################\r\n");
    print("WELCOME TO THE SERIAL BOOT LOADER\r\n");
    print("WRITTEN BY DANIEL BARNEY\r\n");
    print("####################################\r\n");
again:
    print("waiting for kernel to be sent...\r\n");

    int size = uart_recv();
    size += uart_recv() << 8;
    size += uart_recv() << 16;
    size += uart_recv() << 24;

    if (size > 0x200000 - 0x8000) {
      print(" -- kernel is too large\r\n");
      hexstring(size);
      goto again;
    }

    //inform load to send the kernel
    print("y");

    //load the new kernel into ram
    print("loading kernel...\r\n");
    char *kernel = (char*)0x8000;
    while(size-- > 0) {
    	*kernel++ = uart_recv();
    }
    for(size=0;size<0x100000;size++) dummy(size);
    print("booting kernel\r\n");
    asm("bl 0x8000");
    print("halting\r\n");
    return(0);
}
