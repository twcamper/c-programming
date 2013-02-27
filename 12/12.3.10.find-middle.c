#include <stdio.h>

int *find_middle(int *a, int n)
{
  /* return a + (((a + n) - a) / 2); */
  int *low_ptr = a;
  int *high_ptr = low_ptr + n;

  return low_ptr + ((high_ptr - low_ptr) / 2);
}

int main(void)
{
  int ar[9] = {0,1,2,3,4,5,6,7,8};

  int *mid_ptr = find_middle(ar+3, 9);

  printf("%p: %d\n", mid_ptr, *mid_ptr);
  return 0;
}
