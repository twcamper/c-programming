#include <stdio.h>

#define NUM_RATES ((int) (sizeof(value) / sizeof(value[0])))
#define INITIAL_BALANCE 100.00

int main(void)
{
  int i, low_rate, num_years, year;
  double value[5];

  printf("Enter interest rate: ");
  scanf("%d", &low_rate);
  printf("Enter number of years: ");
  scanf("%d", &num_years);

  printf("\nYears");
  for (i = 0; i < NUM_RATES; i++) {
    printf("%6d%%", low_rate + i);
    value[i] = INITIAL_BALANCE;
  }
  printf("\n");

  for (year = 1; year <= num_years; year++)  {
    printf("%3d    ", year);
    for (i = 0; i < NUM_RATES; i++ ) {
      value[i] += ( low_rate + i) / 100.00 * value[i];
      printf("%7.2f", value[i]);
    }
  printf("\n");
  }

  return 0;
}

/*
declare working integer variables
declare array to hold 5 balances: a working value for each of 5 rates we'll be compounding anually
ask user for a rate which will be used as the first as our series of 5 which increase incrementally by 1%
ask user for a number of years over to which to compound the interest for each of the 5 rates
calculate the 4 remaining rates
display the 5 rates in a header row
for each rate, initialize its working array element to $100.00
for each year
    display the year in the header col
        for each rate
            calculate and display the new annual balance based on the balance stored in the rate's array element, and replace
            the old array element value with the new one for use in the next year's iteration for that same rate

*/
