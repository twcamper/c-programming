#include <stdio.h>

int main(void)
{
  int x, tmp;

  int cf1, cf2, cf3, cf4, cf5, cf6; /* coefficients */

  printf("3x^5 + 2x^4 - 5x^3 - x^2 + x7 - 6\n");
  printf("Enter a value for x: ");
  scanf("%d", &x);

  tmp = 3 * x;
  cf1 = tmp * tmp * tmp * tmp * tmp;
  tmp = 2 * x;
  cf2 = tmp * tmp * tmp * tmp;
  tmp = 5 * x;
  cf3 = tmp * tmp * tmp;
  cf4 = x * x;
  cf5 = 7 * x;
  cf6 = 6;

  printf("result: %d\n",  cf1 + cf2 - cf3 - cf4 + cf5 - cf6);

  return 0;
}
