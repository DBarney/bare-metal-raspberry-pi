#include "common.h"
#include "gpio.h"
#include "error.h"

// configure a GPIO pin as input/output etc
#define GPFSEL0 (0x20200000)
#define GPFSEL1 (0x20200004)
#define GPFSEL2 (0x20200008)
#define GPFSEL3 (0x2020000C)
#define GPFSEL4 (0x20200010)
#define GPFSEL5 (0x20200014)

// set a GPIO pin to be high
#define GPSET0  (0x2020001C)
#define GPSET1  (0x20200020)

// set a GPIO pin to be low
#define GPCLR0  (0x20200028)
#define GPCLR1  (0x2020002C)

// get current state of pin high or low
#define GPLEV0  (0x20200034)
#define GPLEV1  (0x20200038)

// stores which pins have edge events that have occured
#define GPEDS0  (0x20200040)
#define GPEDS1  (0x20200044)

// enable a rising edge (011) detection on a GPIO pin
#define GPREN0  (0x2020004C)
#define GPREN1  (0x20200050)

// enable a falling edge (100) detection on a GPIO pin
#define GPFEN0  (0x20200058)
#define GPFEN1  (0x2020005C)

int gpio_configure(PIN pin, unsigned int config)
{
  unsigned int address = 0;
  switch (pin)
  {
    case GPIO_0:
    case GPIO_1:
    case GPIO_2:
    case GPIO_3:
    case GPIO_4:
    case GPIO_5:
    case GPIO_6:
    case GPIO_7:
    case GPIO_8:
    case GPIO_9:
      address = GPFSEL0;
      break;
    case GPIO_10:
    case GPIO_11:
    case GPIO_12:
    case GPIO_13:
    case GPIO_14:
    case GPIO_15:
    case GPIO_16:
    case GPIO_17:
    case GPIO_18:
    case GPIO_19:
      address = GPFSEL1;
      pin <<= 10;
      break;
    case GPIO_20:
    case GPIO_21:
    case GPIO_22:
    case GPIO_23:
    case GPIO_24:
    case GPIO_25:
    case GPIO_26:
    case GPIO_27:
    case GPIO_28:
    case GPIO_29:
      address = GPFSEL2;
      pin <<= 20;
      break;
    case GPIO_30:
    case GPIO_31:
    case GPIO_32:
    case GPIO_33:
    case GPIO_34:
    case GPIO_35:
    case GPIO_36:
    case GPIO_37:
    case GPIO_38:
    case GPIO_39:
      address = GPFSEL3;
      pin <<= 30;
      break;
    case GPIO_40:
    case GPIO_41:
    case GPIO_42:
    case GPIO_43:
    case GPIO_44:
    case GPIO_45:
    case GPIO_46:
    case GPIO_47:
    case GPIO_48:
    case GPIO_49:
      address = GPFSEL4;
      pin <<= 40;
      break;
    case GPIO_50:
    case GPIO_51:
    case GPIO_52:
    case GPIO_53:
      address = GPFSEL5;
      pin <<= 50;
      break;
  }

  unsigned int blank = 7;
  switch (pin)
  {
    case GPIO_0:
      break;
    case GPIO_1:
      config <<= 3;
      blank <<= 3;
      break;
    case GPIO_2:
      config <<= 6;
      blank <<= 6;
      break;
    case GPIO_3:
      config <<= 9;
      blank <<= 9;
      break;
    case GPIO_4:
      config <<= 12;
      blank <<= 12;
      break;
    case GPIO_5:
      config <<= 15;
      blank <<= 15;
      break;
    case GPIO_6:
      config <<= 18;
      blank <<= 18;
      break;
    case GPIO_7:
      config <<= 21;
      blank <<= 21;
      break;
    case GPIO_8:
      config <<= 24;
      blank <<= 24;
      break;
    case GPIO_9:
      config <<= 27;
      blank <<= 27;
      break;
  }

  // get the current config, and layer in the change for the
  // single pin
  unsigned int current = GET32(address);
  current &= ~blank;
  current |= config;
  PUT32(address, current);
  return 0;
}

void gpio_set(PIN pins)
{
  PUT32(GPSET0, pins & 0xffff);
  PUT32(GPSET1, pins >> 32);
}

void gpio_clear(PIN pins)
{
  PUT32(GPCLR0, pins & 0xffff);
  PUT32(GPCLR1, pins >> 32);
}

PIN gpio_high()
{
  return GET32(GPLEV0) | (((PIN)GET32(GPLEV1)) << 32);
}

PIN gpio_low()
{
  return ~gpio_high();
}

void gpio_enable_rising_edge(PIN pins)
{
  PUT32(GPREN0, pins & 0xffff);
  PUT32(GPREN1, pins >> 32);
}

void gpio_enable_falling_edge(PIN pins)
{
  PUT32(GPFEN0, pins & 0xffff);
  PUT32(GPFEN1, pins >> 32);
}

PIN _gpio_changed(int r1, int r2, PIN pins)
{
  if (pins == 0)
  {
    pins = GET32(GPEDS0) | (((PIN)GET32(GPEDS1)) << 32);
  }
  pins = pins & (GET32(r1) | (((PIN)GET32(r2)) << 32));

  // mark the pins as checked
  PUT32(GPEDS0,~pins & 0xffff);
  PUT32(GPEDS1,~pins >> 32);
  return pins;
}

PIN gpio_risen(PIN pins)
{
  return _gpio_changed(GPREN0, GPREN1, pins);
}

PIN gpio_fallen(PIN pins)
{
  return _gpio_changed(GPFEN0, GPFEN1, pins);
}

void activity_on()
{
  gpio_set(GPIO_47);
}

void activity_off()
{
  gpio_clear(GPIO_47);
}
