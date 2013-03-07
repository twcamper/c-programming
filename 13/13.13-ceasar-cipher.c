#include <stdio.h>
#include <ctype.h>

void encrypt(char *s, int shift)
{
  for (; *s; s++) {
    if (islower(*s))
      *s = (( *s - 'a') + shift) % 26 + 'a';
    if (isupper(*s))
      *s = (( *s - 'A') + shift) % 26 + 'A';
  }
}

#define SIZE ( (int) (sizeof(message) / sizeof(message[0])) )

int main(void)
{
  char message[80];
  char ch;
  int i, shift_amount;

  printf("Enter message to be encrypted: ");

  for (i = 0; i < SIZE && (ch = getchar()) != '\n'; i++) {
    message[i] = ch;
  }
  message[i] = '\0';

  printf("Enter shift amount (1-25): ");
  scanf("%d", &shift_amount);

  encrypt(message, shift_amount);
  printf("Encrypted message: %s\n", message);

  return 0;
}
