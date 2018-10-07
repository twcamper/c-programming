#include <stdio.h>

int main(void)
{
  float num1, num2, denom1, denom2, resultnum, resultdenom;

  printf("Enter two fractions separated by a plus sign: ");
  scanf("%f / %f + %f / %f", &num1, &denom1, &num2, &denom2);

  result_num = num1 * denom2 + num2 * denom1;
  result_denom = denom1 * denom2;

  printf("The sum is %f/%f\n", result_num, result_denom);

  return 0;
}
