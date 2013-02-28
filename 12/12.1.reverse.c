#include <stdio.h>

#define SIZE 255
int main(void)
{
  char ch, message[SIZE];
  int i;
  printf("Enter a message up to %d characters: ", SIZE);
  for (i = 0; i < SIZE && (ch = getchar()) != '\n'; i++)
    message[i] = ch;

  printf("Reversed: ");
  for (; i >= 0; i--)
    printf("%c", message[i]);

  printf("\n");

  return 0;
}
