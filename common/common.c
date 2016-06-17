#include "common.h"

// init initializes the raspberry pi to a known state. setups the uart device
// and then blinks the LED to confirm that everything is correct
void init()
{
  unsigned int ra;

  ra=GET32(GPFSEL4);
  ra&=~(7<<21);
  ra|=1<<21;
  PUT32(GPFSEL4,ra);

  activity_on();
  for(ra=0;ra<0x100000;ra++) dummy(ra);
  activity_off();

  uart_init();

  for(int i=0; i < 2; i++) {
    for(ra=0;ra<0x80000;ra++) dummy(ra);
    activity_on();
    for(ra=0;ra<0x80000;ra++) dummy(ra);
    activity_off();
  }
  activity_off();
}

//sets the activity LED to ON
void activity_on()
{
  PUT32(GPSET1,1<<(47-32));
}

//sets the activity LED to OFF
void activity_off()
{
  PUT32(GPCLR1,1<<(47-32));
}
