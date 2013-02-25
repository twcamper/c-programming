#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void split_time(long total_sec, int *hr, int *min, int *sec)
{
  *hr  = total_sec / ( 60 * 60 );
  *min = total_sec % ( 60 * 60 ) / 60;
  *sec = total_sec % 60;
}

int main(int argc, char *argv[])
{
  int hr, min, sec;

  if (argc > 1) {
    /* 1 hour, 1 min, 1 sec */
    split_time(atoi(argv[1]), &hr, &min, &sec);
    printf("%d:%d:%d\n", hr, min, sec);
  }

  /* now */
  split_time(time(NULL), &hr, &min, &sec);

  return 0;
}
