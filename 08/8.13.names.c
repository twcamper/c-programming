#include <stdio.h>

int main(void)
{
  char first[20];
  char last[20];

  printf("Enter a first and last name: ");
  scanf("%20s %20s", &first, &last);

  printf("You entered the name: %s, %c.\n", last, first[0]);
  return 0;
}
