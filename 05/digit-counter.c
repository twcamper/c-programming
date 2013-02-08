#include <stdio.h>

int main(void)
{
  int input, absolute_value, count;

  printf("Enter a number: ");
  scanf("%d", &input);

  absolute_value = input < 1 ? input * -1 : input;
  if (absolute_value < 10)
    count = 1;
  else if (absolute_value < 100)
    count = 2;
  else if (absolute_value < 1000)
    count = 3;
  else if (absolute_value < 10000)
    count = 4;
  printf("The number %d has %d digits\n", input, count);
  return 0;
}
