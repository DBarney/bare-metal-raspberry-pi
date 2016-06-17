#include "common/common.h"

//-------------------------------------------------------------------------
int notmain ( void )
{
    init();
    while (1) {
      int c = uart_recv();
      uart_send(c);
      uart_flush();
    }
    return(0);
}
