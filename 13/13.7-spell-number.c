#include <stdio.h>

int toi(char digit)
{
  return (int) digit - '0';
}
char *get_ones(char digit)
{
  char *ones[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  return ones[toi(digit) - 1];
}
char *get_tens(char digit)
{
  char *tens[] = {"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
  return tens[toi(digit) - 2];
}
char *get_teens(char digit)
{
  char *teens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen",
                   "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
  return teens[toi(digit)];
}
int main(void)
{
  char ones, tens;
  printf("Enter a two-digit number: ");
  scanf("%1c%1c", &tens, &ones);

  if (tens == '1')
    printf("%s\n", get_teens(ones));
  else if (ones == '0')
    printf("%s\n", get_tens(tens));
  else
    printf("%s-%s\n", get_tens(tens), get_ones(ones));

  return 0;
}
