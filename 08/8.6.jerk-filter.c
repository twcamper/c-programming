#include <stdio.h>
#include <ctype.h>

#define SIZE 255
int main(void)
{
  int i;
  char message[SIZE];
  char ch;

  printf("Enter message: ");
  for (i = 0; i < SIZE && (ch = getchar()) != '\n'; i++) {
    message[i] = ch;
  }
  message[i] = '\0';

  printf("In J3rk-speak: ");
  for (i = 0; message[i] != '\0';i++) {
    ch = toupper(message[i]);
    switch (ch) {
    case 'A':
      ch = '4';
      break;
    case 'B':
      ch = '8';
      break;
    case 'E':
      ch = '3';
      break;
    case 'I':
      ch = '1';
      break;
    case 'L':
      ch = '1';
      break;
    case 'O':
      ch = '0';
      break;
    case 'S':
      ch = '5';
      break;
    }
    printf("%c", ch);
  }
  printf("!!!!!!!!!!!!\n");

  return 0;
}
