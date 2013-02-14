#include <stdio.h>

int main(void)
{
  int n;

  printf("This program creates a magic square of a specified size.\nThe size must be an odd number between 1 and 99\n");
  printf("Enter the size of the magic square: ");
  scanf("%d", &n);

  /*validate input*/
  if ((n % 2) == 0 || n < 1 || n > 99)  {
    fprintf(stderr, "Enter an ODD number between 1 and 99\n");
    return 1;
  }

  char square[n][n];

  return 0;
}
