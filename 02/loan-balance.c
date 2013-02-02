#include <stdio.h>

int main(void)
{

  float balance, rate, monthly_rate, interest, payment;

  printf("Enter amount of loan: ");
  scanf("%f", &balance);
  printf("Enter interest rate: ");
  scanf("%f", &rate);
  printf("Enter monthly payment: ");
  scanf("%f", &payment);

  monthly_rate = (rate * 0.01f) / 12.0;

  interest     = balance * monthly_rate;
  balance      += interest;
  balance      = balance - payment;

  printf("Balance after payment 1: $%.2f\n", balance);

  interest     = balance * monthly_rate;
  balance      += interest;
  balance      = balance - payment;

  printf("Balance after payment 2: $%.2f\n", balance);

  interest     = balance * monthly_rate;
  balance      += interest;
  balance      = balance - payment;

  printf("Balance after payment 3: $%.2f\n", balance);

  return 0;
}
