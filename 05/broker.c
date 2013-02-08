/* Calculate a broker's commission */
#include <stdio.h>

int main(void)
{
  int shares;
  float price, commission, value, percentage, base;
  float minimum = 39.00;

  printf("Number of shares: ");
  scanf("%d", &shares);

  printf("Price per share: ");
  scanf("%f", &price);

  value = price * shares;

  if (value < 2500.00f) {
    base = 30.00;
    percentage = .017;
  } else if (value < 6250.00f) {
    base = 56.00; 
    percentage = .0066;
  } else if (value < 2000.00f) {
    base = 76.00;
    percentage = .0034;
  } else if (value < 50000.00f) {
    base = 100.00;
    percentage = .0022;
  } else if (value < 500000.00f) {
    base = 155.00;
    percentage = .0011;
  } else {
    base = 255.00;
    percentage = .0009;
  }

  commission = base + percentage * value;

  if (commission < minimum)
    commission = minimum;

  printf("Our Commission: $%.2f\n", commission);

  base = 33.00;
  percentage = 0.02;
  if (shares > 2000) 
    percentage = 0.03;

  commission = base + shares * percentage;
  printf("Their Commission: $%.2f\n", commission);

  return 0;
}
