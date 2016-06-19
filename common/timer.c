#include "common.h"

#define ARM_TIMER_CTL   (0x2000B408)
#define ARM_TIMER_CNT   (0x2000B420)

void timer_init()
{
    //0xF9+1 = 250
    //250MHz/250 = 1MHz
    PUT32(ARM_TIMER_CTL,0x00F90000);
    PUT32(ARM_TIMER_CTL,0x00F90200);
}

unsigned int timer_tick()
{
    return(GET32(ARM_TIMER_CNT));
}
