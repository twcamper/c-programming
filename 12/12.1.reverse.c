#include <stdio.h>

#define SIZE 25
int main(void)
{
  char ch, message[SIZE];
  char *ptr;
  printf("Enter a message up to %d characters: ", SIZE);
  for (ptr = message; ptr < message + SIZE && (ch = getchar()) != '\n'; ptr++)
    *ptr = ch;

  printf("Reversed: ");
  for (; ptr >= message; ptr--)
    printf("%c", *ptr);

  printf("\n");

  return 0;
}
