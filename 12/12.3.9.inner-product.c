#include <stdio.h>

#define SIZE 5
double inner_product(const double *a, const double *b, int n)
{
  const double *a_ptr, *b_ptr;
  double product = 0.0;

  for (a_ptr = a, b_ptr = b; a_ptr < a + n && b_ptr < b + n; a_ptr++, b_ptr++)
    product += *a_ptr * *b_ptr;
  return product;
}

int main(void)
{
  double ar1[SIZE] = {1.0, 3.145, 7.8, -22.05, 99.99};
  double ar2[SIZE] = {3.0, 1.15, 8.8, -22.05, 19.099};

  printf("Product: %3.8f\n", inner_product(ar1, ar2, SIZE));

  return 0;
}
