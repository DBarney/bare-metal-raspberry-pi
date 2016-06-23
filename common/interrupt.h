#include "handler.h"

#ifndef _KERNEL_INTERRUPT
#define _KERNEL_INTERRUPT

typedef unsigned long long INT;

//inturrupts for handling illegal access
#define IRQ_ILLEGAL_0 ((INT)(1 << 7))
#define IRQ_ILLEGAL_1 ((INT)(1 << 6))

//inturrupts for handling GPU halts
#define IRQ_GPU_HALT_0 ((INT)(1 << 5))
#define IRQ_GPU_HALT_1 ((INT)(1 << 4))

//inturrupts for handling doorbells
#define IRQ_DOORBELL_0 ((INT)(1 << 3))
#define IRQ_DOORBELL_1 ((INT)(1 << 2))

//inturrupts for handling the mailbox
#define IRQ_MAILBOX ((INT)(1 << 1))

//inturrupts for handling the timer
#define IRQ_TIMER ((INT)(1))

// start the interrupt system
void interrupt_start();

//enable/disable specific sets of inturrupts
void interrupt_enable(INT interrupt);
void interrupt_disable(INT interrupt);

//set the handler for timer interrupts
void interrupt_set_timer_handler(handler timer);

//get the interrupt status
unsigned int interrupt_get_status();
void c_irq_handler();

#endif
