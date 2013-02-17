#include <stdio.h>
/*Write a single expression whose value is either -1, 0, or +1, 
  depending on whether i is less than, equal to, or greater than j, respectively.*/

void test(int i, int j)
{
  int result = i < j ? -1 : i > j;

  /*The following 2 also work*/
  /*result = i < j ? -1 : ( i > j );*/
  /*result = i < j ? -1 : ( i == j ? 0 : 1);*/
  printf("i=%d, j=%d: %d\n", i, j, result);
}

int main(void)
{
  test(1,2);
  test(2,2);
  test(2,1);

  return 0;
}
