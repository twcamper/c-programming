#include <time.h>

void split_time(long total_sec, int *hr, int *min, int *sec)
{
  *hr  = total_sec / ( 60 * 60 );
  *min = *hr % 60;
  *sec = total_sec % 60;
}

int main(void)
{
  int hr, min, sec;

  /* 1 hour, 1 min, 1 sec */
  split_time(3661, &hr, &min, &sec);
  /* now */
  split_time(time(NULL), &hr, &min, &sec);
  return 0;
}
