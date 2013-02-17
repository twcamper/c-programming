#include <stdio.h>
#include <ctype.h>

int main(void)
{
  char message[80];
  char ch;
  int i, length, shift_amount;

  printf("Enter message to be encrypted: ");

  for (i = 0; (ch = getchar()) != '\n'; i++) {
    message[i] = ch;
  }
  length = i;

  printf("Enter shift amount (1-25): ");
  scanf("%d", &shift_amount);

  printf("Encrypted message: ");

  for (i = 0; i < length; i++) {
    ch = message[i];
    if (ch >= 'a' && ch <= 'z')
      ch = (( ch - 'a') + shift_amount) % 26 + 'a';
    if (ch >= 'A' && ch <= 'Z')
      ch = (( ch - 'A') + shift_amount) % 26 + 'A';

    printf("%c", ch);
  }
  puts("");
  return 0;
}
