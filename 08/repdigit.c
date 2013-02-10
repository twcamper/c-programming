#include <stdio.h>
#include <stdbool.h>

int main(void)
{
  int digits[10] = {0};
  int digit;
  bool any_repeats = false;
  long n;

  printf("Enter a number: ");
  scanf("%ld", &n);

  while (n > 0)  {
    digit = n % 10;
    digits[digit]++;
    if (!any_repeats && digits[digit] > 1)
      any_repeats = true;
    n /= 10;
  }

  if (any_repeats) {
    printf("Repeated digit(s): ");
    for (digit = 0; digit < 10; digit++) {
      if (digits[digit] > 1)
        printf("%2d", digit);
    }
    puts("");
  }
  else
    printf("No repeated digit\n");

  return 0;
}
