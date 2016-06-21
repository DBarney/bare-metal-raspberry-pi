#include "handler.h"

#ifndef _KERNEL_TIMER
#define _KERNEL_TIMER

// I should find the right values for these
#define TIMER_MINUTE (TIMER_SECOND * 60)
#define TIMER_SECOND 0x0100000
#define TIMER_MILLISECOND (TIMER_SECOND/1000)
#define TIMER_NANOSECOND (TIMER_MILLISECOND/1000)

// set a function to call when after has passed, returns when the timer should fire
unsigned int timer_enable_0(handler func, int after);
unsigned int timer_enable_1(handler func, int after);
unsigned int timer_enable_2(handler func, int after);
unsigned int timer_enable_3(handler func, int after);

// checks and calls all timers that have fired
void timer_call_active_timers();

// returns the current status of the timers
unsigned int timer_fired();
unsigned int timer_now();

#endif
