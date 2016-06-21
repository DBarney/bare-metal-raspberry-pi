#include "common.h"
#include "interrupt.h"

#define IRQ_BASIC 0x2000B200
#define IRQ_1 0x2000B204
#define IRQ_2 0x2000B208

#define FIQ_CONTROLL 0x2000B20C

#define IRQ_ENABLE_1 0x2000B210
#define IRQ_ENABLE_2 0x2000B214
#define IRQ_ENABLE_BASIC 0x2000B218

#define IRQ_DISABLE_1 0x2000B21C
#define IRQ_DISABLE_2 0x2000B220
#define IRQ_DISABLE_BASIC 0x2000B224


#define IRQ_GPU_62 (1 << 20)
#define IRQ_GPU_57 (1 << 19)
#define IRQ_GPU_56 (1 << 18)
#define IRQ_GPU_55 (1 << 17)
#define IRQ_GPU_54 (1 << 16)
#define IRQ_GPU_53 (1 << 15)
#define IRQ_GPU_19 (1 << 14)
#define IRQ_GPU_18 (1 << 13)
#define IRQ_GPU_10 (1 << 12)
#define IRQ_GPU_9 (1 << 11)
#define IRQ_GPU_7 (1 << 10)

#define IRQ_PENDING_1 (1 << 9)
#define IRQ_PENDING_2 (1 << 8)

handler timerHandler = NOOP;

void interrupt_enable(INT interrupt)
{
    PUT32(IRQ_ENABLE_BASIC, interrupt & 0xffff);
    // PUT32(IRQ_ENABLE_2, interrupt >> 32);
}

void interrupt_disable(INT interrupt)
{
  PUT32(IRQ_ENABLE_BASIC, interrupt & 0xffff);
  // PUT32(IRQ_DISABLE_2, interrupt >> 32);
}

void interrupt_set_timer_handler(handler timer)
{
  timerHandler = timer;
}

unsigned int interrupt_get_status()
{
  return GET32(IRQ_BASIC);
}

void c_irq_handler()
{
  int fired = GET32(IRQ_BASIC);
  if (fired & IRQ_TIMER) {
    timerHandler();
  }
}
