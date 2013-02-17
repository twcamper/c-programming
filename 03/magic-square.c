#include <stdio.h>

int main(void)
{
  int r1c1, r1c2, r1c3, r1c4;
  int r2c1, r2c2, r2c3, r2c4;
  int r3c1, r3c2, r3c3, r3c4;
  int r4c1, r4c2, r4c3, r4c4;

  char *row_format = "%2d\t%2d\t%2d\t%2d\n";
  printf("Enter the numbers from 1 to 16 in any order:\n");
  scanf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",\
      &r1c1, &r1c2, &r1c3, &r1c4, \
      &r2c1, &r2c2, &r2c3, &r2c4, \
      &r3c1, &r3c2, &r3c3, &r3c4, \
      &r4c1, &r4c2, &r4c3, &r4c4);
  
  printf(row_format, r1c1, r1c2, r1c3, r1c4);
  printf(row_format, r2c1, r2c2, r2c3, r2c4);
  printf(row_format, r3c1, r3c2, r3c3, r3c4);
  printf(row_format, r4c1, r4c2, r4c3, r4c4);

  printf("Row sums: %2d  %2d  %2d  %2d\n", \
      r1c1 + r1c2 + r1c3 + r1c4, \
      r2c1 + r2c2 + r2c3 + r2c4, \
      r3c1 + r3c2 + r3c3 + r3c4, \
      r4c1 + r4c2 + r4c3 + r4c4);
  printf("Column sums: %2d  %2d  %2d  %2d\n", \
      r1c1 + r2c1 + r3c1 + r4c1, \
      r1c2 + r2c2 + r3c2 + r4c2, \
      r1c3 + r2c3 + r3c3 + r4c3, \
      r1c4 + r2c4 + r3c4 + r4c4);

  printf("Diagonal sums: %2d  %2d\n", \
      r1c1 + r2c2 + r3c3 + r4c4, \
      r4c1 + r3c2 + r2c3 + r1c4);
  return 0;
}
