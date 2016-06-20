#include "../../common/common.h"
#include "../../common/gpio.h"
#include "../../common/uart.h"

//-------------------------------------------------------------------------
int kmain ( void )
{
    init();
    gpio_configure(GPIO_18, GPIO_INPUT);
    uart_print("counting transitions\r\n");

    unsigned int count = 0;
    unsigned int state = 0;
    while (1)
    {
      if (state == 0 && ((gpio_high() & GPIO_18) == GPIO_18))
      {
        state = 1;
        count++;
      } else if (state == 1 && ((gpio_low() & GPIO_18) == GPIO_18))
      {
        state = 0;
        count++;
      }
      uart_hexstrings(count);
      uart_print("\r");
    }
    return(0);
}
