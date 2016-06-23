#include "../../common/common.h"
#include "../../common/gpio.h"
#include "../../common/uart.h"
#include "../../common/timer.h"
#include "../../common/interrupt.h"
#include "../../common/handler.h"

volatile unsigned int flag = 1;
void unpause();

int kmain ( void )
{
    init();
    uart_print("printing to the console based on inturrupts\r\n");

    flag = 1;
    // check to see if the timer works correctly
    activity_on();
    timer_enable_1(unpause, TIMER_SECOND);
    while(flag) timer_call_active_timers();
    uart_print("the timer did fire\r\n");
    activity_off();
    flag = 1;
    timer_enable_1(unpause, TIMER_SECOND);
    while(flag) timer_call_active_timers();
    uart_print("the timer did fire\r\n");
    activity_on();

    // enable the IRQ for the timer
    interrupt_enable(IRQ_TIMER);
    interrupt_set_timer_handler(timer_call_active_timers);

    flag = 1;
    timer_enable_1(unpause, TIMER_SECOND);
    while(flag) c_irq_handler();
    uart_print("the irq was sent\r\n");
    activity_off();
    flag = 1;
    timer_enable_1(unpause, TIMER_SECOND);
    while(flag) c_irq_handler();
    uart_print("the irq was sent\r\n");
    activity_on();

    // start handling inturrupts
    interrupt_start();
    while(1) {
      flag = 1;
      timer_enable_1(unpause, TIMER_SECOND);
      while(flag);
      uart_print("the interrupt was called\r\n");
      activity_off();
      flag = 1;
      timer_enable_1(unpause, TIMER_SECOND);
      while(flag);
      uart_print("the interrupt was called\r\n");
      activity_on();
    }

    return(0);
}

void unpause()
{
  flag = 0;
}
