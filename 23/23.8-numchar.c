#include <string.h>
#include "test_runner.h"

int numchar(const char *s, char ch)
{
  int count = 0;
  const char *p = s;
  while ((p = strchr(p, ch))) {
    count++;
    p++;
  }

  return count;
}
int numchar_test(void)
{
  _assert(numchar("aardvark", 'a') == 3);
  _assert(numchar("aardvark", 'q') == 0);
  _assert(numchar("aardvark", 'k') == 1);

  return 0;
}
int all_tests(void)
{
  _run(numchar_test);
  return 0;
}
