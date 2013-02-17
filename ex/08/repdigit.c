#include <stdio.h>
#define DIGIT_FORMAT "%3d"
#define NUM_DIGITS 10
int main(void)
{
  int digit_counts[NUM_DIGITS];
  int digit;
  long n;

  printf("Enter a number (0 or negative to terminate: ");
  while (scanf("%ld", &n), (n > 0)) {
    for (digit = 0; digit < NUM_DIGITS; digit++) {
      digit_counts[digit] = 0;
    }

    while (n > 0)  {
      digit = n % 10;
      digit_counts[digit]++;
      n /= 10;
    }

    printf("Digit:\t\t");
    for (digit = 0; digit < NUM_DIGITS; digit++) {
      printf(DIGIT_FORMAT, digit);
    }
    puts("");

    printf("Occurrences:\t");
    for (digit = 0; digit < NUM_DIGITS; digit++) {
      printf(DIGIT_FORMAT, digit_counts[digit]);
    }
    puts("");
  }

  return 0;
}
