#ifndef _KERNEL_GPIO
#define _KERNEL_GPIO

typedef unsigned long long PIN;

#define GPIO_0 (1)
#define GPIO_1 (((PIN)1)<<1)
#define GPIO_2 (((PIN)1)<<2)
#define GPIO_3 (((PIN)1)<<3)
#define GPIO_4 (((PIN)1)<<4)
#define GPIO_5 (((PIN)1)<<5)
#define GPIO_6 (((PIN)1)<<6)
#define GPIO_7 (((PIN)1)<<7)
#define GPIO_8 (((PIN)1)<<8)
#define GPIO_9 (((PIN)1)<<9)
#define GPIO_10 (((PIN)1)<<10)
#define GPIO_11 (((PIN)1)<<11)
#define GPIO_12 (((PIN)1)<<12)
#define GPIO_13 (((PIN)1)<<13)
#define GPIO_14 (((PIN)1)<<14)
#define GPIO_15 (((PIN)1)<<15)
#define GPIO_16 (((PIN)1)<<16)
#define GPIO_17 (((PIN)1)<<17)
#define GPIO_18 (((PIN)1)<<18)
#define GPIO_19 (((PIN)1)<<19)
#define GPIO_20 (((PIN)1)<<20)
#define GPIO_21 (((PIN)1)<<21)
#define GPIO_22 (((PIN)1)<<22)
#define GPIO_23 (((PIN)1)<<23)
#define GPIO_24 (((PIN)1)<<24)
#define GPIO_25 (((PIN)1)<<25)
#define GPIO_26 (((PIN)1)<<26)
#define GPIO_27 (((PIN)1)<<27)
#define GPIO_28 (((PIN)1)<<28)
#define GPIO_29 (((PIN)1)<<29)
#define GPIO_30 (((PIN)1)<<30)
#define GPIO_31 (((PIN)1)<<31)
#define GPIO_32 (((PIN)1)<<32)
#define GPIO_33 (((PIN)1)<<33)
#define GPIO_34 (((PIN)1)<<34)
#define GPIO_35 (((PIN)1)<<35)
#define GPIO_36 (((PIN)1)<<36)
#define GPIO_37 (((PIN)1)<<37)
#define GPIO_38 (((PIN)1)<<38)
#define GPIO_39 (((PIN)1)<<39)
#define GPIO_40 (((PIN)1)<<40)
#define GPIO_41 (((PIN)1)<<41)
#define GPIO_42 (((PIN)1)<<42)
#define GPIO_43 (((PIN)1)<<43)
#define GPIO_44 (((PIN)1)<<44)
#define GPIO_45 (((PIN)1)<<45)
#define GPIO_46 (((PIN)1)<<46)
#define GPIO_47 (((PIN)1)<<47)
#define GPIO_48 (((PIN)1)<<48)
#define GPIO_49 (((PIN)1)<<49)
#define GPIO_50 (((PIN)1)<<50)
#define GPIO_51 (((PIN)1)<<51)
#define GPIO_52 (((PIN)1)<<52)
#define GPIO_53 (((PIN)1)<<53)

#define GPIO_INPUT  (0x000)
#define GPIO_OUTPUT (0x001)
#define GPIO_ALT5 (0x010)
#define GPIO_ALT4 (0x011)
#define GPIO_ALT0 (0x100)
#define GPIO_ALT1 (0x101)
#define GPIO_ALT2 (0x110)
#define GPIO_ALT3 (0x111)

// configure a single GPIO pin
int gpio_configure(PIN pin, unsigned int config);

// set GPIO pins to high
void gpio_set(PIN pins);
// set GPIO pins to low
void gpio_clear(PIN pins);

// get all pins that are currently high
PIN gpio_high();
// get all pins that are currently low
PIN gpio_low();

// enable rising edge detection 011
void gpio_enable_rising_edge(PIN pins);
// enable falling edge detection 100
void gpio_enable_falling_edge(PIN pins);

// get pins that have risen, pass in 0 for all pins
PIN gpio_risen(PIN);
// get pins that have fallen, pass in 0 for all pins
PIN gpio_fallen(PIN);

// turn on the activity LED
void activity_on();
// turn off the activity LED
void activity_off();

int gpio_bank(PIN pin, unsigned int config, int which);

#endif
