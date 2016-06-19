#ifndef _KERNEL_UART
#define _KERNEL_UART

// read one character from uart
unsigned int uart_recv();
// send one character on the uart
void uart_send(unsigned char c);
// wait until all the data has been sent
void uart_flush();
//print an int as a hex string with a space afterwards
void uart_hexstrings(unsigned int d);
//print an int as a hex string and move to the next line
void uart_hexstring(unsigned int d);
//init the uart gpio pins
void uart_init();
//print a NULL terminated string to the uart
void uart_print(const char* str);

#endif
