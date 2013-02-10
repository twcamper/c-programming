#include <stdio.h>
#define DIGIT_FORMAT "%3d"
int main(void)
{
  int digit_counts[10] = {0};
  int digit;
  long n;

  printf("Enter a number: ");
  scanf("%ld", &n);

  while (n > 0)  {
    digit = n % 10;
    digit_counts[digit]++;
    n /= 10;
  }

  printf("Digit:\t\t");
  for (digit = 0; digit < 10; digit++) {
    printf(DIGIT_FORMAT, digit);
  }
  puts("");

  printf("Occurrences:\t");
  for (digit = 0; digit < 10; digit++) {
    printf(DIGIT_FORMAT, digit_counts[digit]);
  }
  puts("");

  return 0;
}
