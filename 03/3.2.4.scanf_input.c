#include <stdio.h>

int main(void)
{

  int i, j;
  float x;

  scanf("%d%f%d", &i, &x, &j);

  printf("i: %d\nx: %.2f\nj: %d\n", i, x, j);
  return 0;

  /*
   * I was right!  Since "." can't be part of an int,
   * processing of int i stops at the dot, and processing of float x
   * STARTS at the dot.
   *
  tim@fern:~/c/c-programming$ 03/3.2.4.scanf_input
    10.3 5 6
    i: 10
    x: 0.30
    j: 5
    */
}
