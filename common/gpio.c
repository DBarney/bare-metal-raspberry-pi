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
  // only let the first 3 bits though as a valid config
  config = config & 0x7;

  unsigned int address = 0;
  PIN condition = 0;
  if (pin < GPIO_10) {
    condition = GPIO_0;
    address = GPFSEL0;
  } else if (pin < GPIO_20) {
    condition = GPIO_10;
    address = GPFSEL1;
  } else if (pin < GPIO_30) {
    condition = GPIO_20;
    address = GPFSEL2;
  } else if (pin < GPIO_40) {
    condition = GPIO_30;
    address = GPFSEL3;
  } else if (pin < GPIO_50) {
    condition = GPIO_40;
    address = GPFSEL4;
  } else if (pin <= GPIO_53) {
    condition = GPIO_50;
    address = GPFSEL5;
  } else {
    return EINVALID;
  }

  // shift the config to the right spot with some bits to
  // blank out the old config
  unsigned blank = 7;
  for (; pin & condition; pin >>= 1)
  {
    blank <<= 3;
    config <<= 3;
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
