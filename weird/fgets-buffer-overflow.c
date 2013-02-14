/* Copied from 08/8.15.ceasar-cipher.c
 *
 * fgets() should just truncate input to the array's size, 
 * but in this program when you go beyond 80, the scanf() call is
 * skipped, and our input message, truncated, is simply printed out
 * appended to the printf "Encrypted message: " line.
 * 
 *
 * tim@fern:~/c/c-programming$ make
 * gcc -c -g3 -gdwarf-4 -Wall -Wextra -pedantic -std=c99 weird/fgets-buffer-overflow.c -o weird/fgets-buffer-overflow.o
 * gcc weird/fgets-buffer-overflow.o -o weird/fgets-buffer-overflow
 * tim@fern:~/c/c-programming$ weird/fgets-buffer-overflow
 * Enter message to be encrypted: Wow this is going to be a long one buddy, what do you think, do you think it will be a long one too?
 * Enter shift amount (1-25): Encrypted message: Wow this is going to be a long one buddy, what do you think, do you think it wi
 * tim@fern:~/c/c-programming$ echo $?
 * 0
 *
 */ 
#include <stdio.h>
#include <ctype.h>

#define SIZE 80

int main(void)
{
  char message[SIZE];
  char ch;
  int i, shift_amount;

  printf("Enter message to be encrypted: ");
  fgets(message, sizeof(message), stdin);

  printf("Enter shift amount (1-25): ");
  scanf("%d", &shift_amount);

  printf("Encrypted message: ");

  for (i = 0; i < SIZE && (ch = message[i]) != '\n'; i++) {
    if (ch >= 'a' && ch <= 'z')
      ch = (( ch - 'a') + shift_amount) % 26 + 'a';
    if (ch >= 'A' && ch <= 'Z')
      ch = (( ch - 'A') + shift_amount) % 26 + 'A';

    printf("%c", ch);
  }
  puts("");
  return 0;
}
