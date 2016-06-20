#include "../../common/common.h"
#include "../../common/gpio.h"
#include "../../common/uart.h"

int kmain ( void )
{
    init();
    gpio_configure(GPIO_18, GPIO_INPUT);
    gpio_configure(GPIO_23, GPIO_INPUT);
    uart_print("detecting movement\r\n");

    unsigned int count = 0;
    unsigned int state = gpio_high() & (GPIO_18 | GPIO_23);
    while (1)
    {
      unsigned int current = gpio_high() & (GPIO_18 | GPIO_23);
      unsigned int prev = 0;
      if (current == state){
        continue;
      }
      //find out which direction we are moving
      switch (state)
      {
        case 0:
          prev = GPIO_23;
          break;
        case GPIO_18: // 0 1
          prev = 0;
          break;
        case GPIO_18 | GPIO_23: // 1 1
          prev = GPIO_18;
          break;
        case GPIO_23: // 1 0
          prev = GPIO_23 | GPIO_18;
          break;
      }
      if (current == prev) {
        count--;
      } else {
        count++;
      }
      state = current;
      uart_hexstrings(count);
      uart_print("\r");
    }
    return(0);
}
