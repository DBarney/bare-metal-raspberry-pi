#ifndef _KERNEL_HANDLER
#define _KERNEL_HANDLER

//handler is a callback that takes no args and returns no values
typedef void(*handler)();

// a simple noop function
void NOOP();

#endif
