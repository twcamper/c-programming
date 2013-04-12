#include "test_runner.h"

unsigned short int swap_bytes(unsigned short i)
{
  return i << 8 | i >> 8;
}

int swap_bytes_test(void)
{
  _assert(swap_bytes(0x1234) == 0x3412);
  _assert(swap_bytes(0xFF00) == 0x00FF);
  return 0;
}
int all_tests(void)
{

  _run(swap_bytes_test);
  return 0;
}
