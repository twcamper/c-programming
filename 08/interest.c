#include <stdio.h>

#define NUM_RATES ((int) (sizeof(value) / sizeof(value[0])))
#define INITIAL_BALANCE 100.00

int main(void)
{
  int i, m, low_rate, num_years, year;
  /*hold 5 balances: a working value for each of 5 rates we'll be compounding*/
  double value[5];

  printf("Enter interest rate: ");
  scanf("%d", &low_rate);
  printf("Enter number of years: ");
  scanf("%d", &num_years);

  printf("\nYears");
  for (i = 0; i < NUM_RATES; i++) {
    /* calculate the 4 remaining rates*/
    /* and display the 5 rates in a header row*/
    printf("%6d%%", low_rate + i);
    /*for each rate, initialize its working array element to $100.00*/
    value[i] = INITIAL_BALANCE;
  }
  printf("\n");

  for (year = 1; year <= num_years; year++)  {
    printf("%3d    ", year);
    for (i = 0; i < NUM_RATES; i++ ) {
      /*to begin the series of monthly balance calcuations, save off the previous year's balance*/
      /*for the rate we're currently on*/
      for (m = 0; m < 12; m++) {
        value[i] += ((( low_rate + i) / 100.00) / 12.0) * value[i];
      }
      /*accumulated balance for a year of 12 monthtly calcuations: save for display and to seed next year's calc for this rate*/
      printf("%7.2f", value[i]);
    }
  printf("\n");
  }

  return 0;
}
