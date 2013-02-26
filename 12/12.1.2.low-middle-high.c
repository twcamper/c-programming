#include <stdio.h>

int main(void)
{
  int a[] = {0, 1, 2, 3, 4, 5}, *low, *middle, *high;

  low = a;
  high = &a[5];


  printf("low: %p, %d\n", low, *low);
  printf("high: %p, %d\n", high, *high);

  middle = low + (high - low) / 2;

  printf("middle: %p, %d\n", middle, *middle);
  return 0;
}
