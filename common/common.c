#include "common.h"
#include "gpio.h"

// init initializes the raspberry pi to a known state. setups the uart device
// and then blinks the LED to confirm that everything is correct
void init()
{
  gpio_configure(GPIO_21, GPIO_OUTPUT);

  activity_on();
  busy_wait(0x100000);
  activity_off();

  uart_init();

  for(int i=0; i < 2; i++) {
    busy_wait(0x80000);
    activity_on();
    busy_wait(0x80000);
    activity_off();
  }
  activity_off();
}
