#include "../../common/common.h"
#include "../../common/gpio.h"

//-------------------------------------------------------------------------
int kmain ( void )
{
    init();
    print("echoing back what you type\r\n");
    while (1) {
      int c = uart_recv();
      activity_on();
      if (c == '\r')
      {
          uart_send('\r');
          uart_send('\n');
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
