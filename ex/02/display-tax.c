#include <stdio.h>

int main(void)
{
  float amount, tax;

  printf("Enter a dollar amount: ");
  scanf("%f", &amount);

  tax = amount * 0.05f;

  printf("With tax added: $%.2f\n", amount + tax);

 /*nicer solution from KNKing (1 less variable)*/
 /*printf("With tax added: $%.2f\n", amount * 1.05f);*/

  return 0;
}
