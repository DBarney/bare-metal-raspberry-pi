#include "common.h"
#include "gpio.h"
#include "wait.h"
#include "uart.h"

#define GPFSEL1         (0x20200004)
#define GPFSEL3         (0x2020000C)
#define GPFSEL4         (0x20200010)
#define GPPUD           (0x20200094)
#define GPPUDCLK0       (0x20200098)

#define AUX_ENABLES     (0x20215004)
#define AUX_MU_IO_REG   (0x20215040)
#define AUX_MU_IER_REG  (0x20215044)
#define AUX_MU_IIR_REG  (0x20215048)
#define AUX_MU_LCR_REG  (0x2021504C)
#define AUX_MU_MCR_REG  (0x20215050)
#define AUX_MU_LSR_REG  (0x20215054)
#define AUX_MU_MSR_REG  (0x20215058)
#define AUX_MU_SCRATCH  (0x2021505C)
#define AUX_MU_CNTL_REG (0x20215060)
#define AUX_MU_STAT_REG (0x20215064)
#define AUX_MU_BAUD_REG (0x20215068)

unsigned int uart_check (unsigned int flag)
{
    return (GET32(AUX_MU_LSR_REG) & flag) == flag;
}

unsigned int uart_recv ( void )
{
    while(uart_check(0x01) == 0);
    return(GET32(AUX_MU_IO_REG)&0xFF);
}

void uart_send ( unsigned char c )
{
    while(uart_check(0x20) == 0);
    PUT32(AUX_MU_IO_REG, c);
}

void uart_flush ( void )
{
    while(uart_check(0x40));
}

void uart_hexstrings ( unsigned int d )
{
    //unsigned int ra;
    unsigned int rb;
    unsigned int rc;

    rb=32;
    while(1)
    {
        rb-=4;
        rc=(d>>rb)&0xF;
        if(rc>9) rc+=0x37; else rc+=0x30;
        uart_send(rc);
        if(rb==0) break;
    }
    uart_send(0x20);
}

void uart_hexstring ( unsigned int d )
{
    uart_hexstrings(d);
    uart_print("\r\n");
}

//print takes a NULL terminated string and dumps it to the console
void uart_print(const char* str)
{
  while(*str) uart_send(*str++);
}


void uart_init ( void )
{
    // unsigned int ra;

    PUT32(AUX_ENABLES,1);
    PUT32(AUX_MU_IER_REG,0);
    PUT32(AUX_MU_CNTL_REG,0);
    PUT32(AUX_MU_LCR_REG,3);
    PUT32(AUX_MU_MCR_REG,0);
    PUT32(AUX_MU_IER_REG,0);
    PUT32(AUX_MU_IIR_REG,0xC6);
    PUT32(AUX_MU_BAUD_REG,270);
    gpio_configure(GPIO_14, GPIO_ALT5);
    gpio_configure(GPIO_15, GPIO_ALT5);
    // ra=GET32(GPFSEL1);
    // ra&=~(7<<12); //gpio14
    // ra|=2<<12;    //alt5
    // ra&=~(7<<15); //gpio15
    // ra|=2<<15;    //alt5
    // PUT32(GPFSEL1,ra);
    PUT32(GPPUD,0);
    busy_wait(150);
    PUT32(GPPUDCLK0,(1<<14)|(1<<15));
    busy_wait(150);
    PUT32(GPPUDCLK0,0);
    PUT32(AUX_MU_CNTL_REG,3);
}
