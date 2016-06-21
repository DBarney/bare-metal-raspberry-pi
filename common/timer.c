#include "common.h"
#include "handler.h"

#define TIMER_STATUS   (0x20003000)

#define TIMER_COUNTER_0   (0x20003004)
#define TIMER_COUNTER_1   (0x20003008)

#define TIMER_COMPARE_0   (0x2000300C)
#define TIMER_COMPARE_1   (0x20003010)
#define TIMER_COMPARE_2   (0x20003014)
#define TIMER_COMPARE_3   (0x20003018)

#define TIMER_FIRED_0 (1)
#define TIMER_FIRED_1 (1 << 1)
#define TIMER_FIRED_2 (1 << 2)
#define TIMER_FIRED_3 (1 << 3)

handler compare_fun0 = NOOP;
handler compare_fun1 = NOOP;
handler compare_fun2 = NOOP;
handler compare_fun3 = NOOP;

unsigned int enable_timer(unsigned int address, int after)
{
  unsigned int at = GET32(TIMER_COUNTER_0) + after;
  PUT32(address, at);
  return at;
}

unsigned int timer_enable_0(handler func, int after)
{
  compare_fun0 = func;
  return enable_timer(TIMER_COMPARE_0, after);
}

unsigned int timer_enable_1(handler func, int after)
{
  compare_fun1 = func;
  return enable_timer(TIMER_COMPARE_1, after);
}

unsigned int timer_enable_2(handler func, int after)
{
  compare_fun2 = func;
  return enable_timer(TIMER_COMPARE_2, after);
}

unsigned int timer_enable_3(handler func, int after)
{
  compare_fun3 = func;
  return enable_timer(TIMER_COMPARE_3, after);
}

unsigned int timer_fired()
{
  return GET32(TIMER_STATUS);
}

unsigned int timer_now()
{
  return GET32(TIMER_COUNTER_0);
}

void timer_call_active_timers()
{
  int fired = GET32(TIMER_STATUS);
  int clear = 0;
  if ((fired & TIMER_FIRED_0) == TIMER_FIRED_0)
  {
    compare_fun0();
    clear |= TIMER_FIRED_0;
  }
  if ((fired & TIMER_FIRED_1) == TIMER_FIRED_1)
  {
    compare_fun1();
    clear |= TIMER_FIRED_1;
  }
  if ((fired & TIMER_FIRED_2) == TIMER_FIRED_2)
  {
    compare_fun2();
    clear |= TIMER_FIRED_2;
  }
  if ((fired & TIMER_FIRED_3) == TIMER_FIRED_3)
  {
    compare_fun3();
    clear |= TIMER_FIRED_3;
  }
  PUT32(TIMER_STATUS, clear);
}
