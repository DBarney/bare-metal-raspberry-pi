#include "../../common/common.h"
#include "../../common/gpio.h"
#include "../../common/uart.h"

//-------------------------------------------------------------------------
int kmain ( void )
{
    init();
    uart_print("echoing back what you type\r\n");
    while (1) {
      int c = uart_recv();
      activity_on();
      if (c == '\r')
      {
          uart_print("\r\n");
      }
      else
      {
      uart_send(c);
      }
      uart_flush();
      activity_off();
    }
    return(0);
}
