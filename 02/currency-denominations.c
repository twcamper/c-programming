#include <stdio.h>

int main(void)
{
  int amount, remainder, twenties, tens, fives, ones;

  printf("Enter a dollar amount: ");
  scanf("%d", &amount);

  twenties  = amount / 20;
  remainder = amount % 20;
  tens      = remainder / 10;
  remainder = remainder % 10;
  fives     = remainder / 5;
  remainder = remainder % 5;
  ones      = remainder;

  printf("$20 bills: %d\n", twenties);
  printf("$10 bills: %d\n", tens);
  printf("$5 bills: %d\n", fives);
  printf("$1 bills: %d\n", ones);

  return 0;
}
