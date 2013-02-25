#include <stdio.h>

void pay_amount(int, int*, int*, int*, int*);

int main(void)
{
  int amount, twenties, tens, fives, ones;

  printf("Enter a dollar amount: ");
  scanf("%d", &amount);

  pay_amount(amount, &twenties, &tens, &fives, &ones);

  printf("$20 bills: %d\n", twenties);
  printf("$10 bills: %d\n", tens);
  printf("$5 bills: %d\n", fives);
  printf("$1 bills: %d\n", ones);

  return 0;
}

void pay_amount(int dollars, int* twenties, int* tens, int* fives, int* ones)
{
  int remainder;

  *twenties  = dollars / 20;
  remainder  = dollars % 20;
  *tens      = remainder / 10;
  remainder  = remainder % 10;
  *fives     = remainder / 5;
  remainder  = remainder % 5;
  *ones      = remainder;

}
