#include "common.h"

// busy_wait waits for a specific number of instruction executions
void busy_wait(unsigned int count)
{
  for (; count > 0; count--) dummy(count);
}
