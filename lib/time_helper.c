#include "time_helper.h"

time_t random_time(void)
{
  return (time_t) rand() % (int) time(NULL);
}

struct tm *random_tm(void)
{
  time_t t = random_time();

  return localtime(&t);
}
