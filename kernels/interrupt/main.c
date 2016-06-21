#include "../../common/common.h"
#include "../../common/gpio.h"
#include "../../common/uart.h"
#include "../../common/timer.h"
#include "../../common/interrupt.h"

volatile unsigned int flag = 1;
void pause();
void unpause();

int kmain ( void )
{
    init();
    uart_print("printing to the console based on inturrupts\r\n");
    int count = 0;
    // when a timer fires, lets call all the handlers that are needed.
    interrupt_set_timer_handler(timer_call_active_timers);
    // enable the IRQ for the timer
    interrupt_enable(IRQ_TIMER);

    while (1) {
      activity_on();
      uart_hexstrings(count);
      uart_print("\n");
      unsigned int at = timer_enable_0(unpause, TIMER_SECOND * 5);
      uart_print("firing at ");
      uart_hexstrings(at);
      uart_print("\n");
      pause();
      activity_off();
      timer_enable_0(unpause, TIMER_SECOND);
      pause();
    }
    return(0);
}

void pause()
{
  while(flag == 1){
    uart_print("\r");
    uart_hexstrings(interrupt_get_status());
    uart_hexstrings(timer_fired());
    uart_hexstrings(timer_now());
  }
  flag = 1;
}

void unpause()
{
  flag = 0;
}
