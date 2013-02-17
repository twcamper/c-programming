#include <stdio.h>
#include <ctype.h>

int main(void)
{
  char phone_number[15];
  char ch;
  int i;
  printf("Enter phone number: ");
  while ((ch = getchar()) != '\n') {
    switch(toupper(ch)) {
      case 'A':
      case 'B':
      case 'C':
        phone_number[i] = '2';
        break;
      case 'D':
      case 'E':
      case 'F':
        phone_number[i] = '3';
        break;
      case 'G':
      case 'H':
      case 'I':
        phone_number[i] = '4';
        break;
      case 'J':
      case 'K':
      case 'L':
        phone_number[i] = '5';
        break;
      case 'M':
      case 'N':
      case 'O':
        phone_number[i] = '6';
        break;
      case 'P':
      case 'Q':
      case 'R':
      case 'S':
        phone_number[i] = '7';
        break;
      case 'T':
      case 'U':
      case 'V':
        phone_number[i] = '8';
        break;
      case 'W':
      case 'X':
      case 'Y':
      case 'Z':
        phone_number[i] = '9';
        break;
      default:
        phone_number[i] = ch;
    }
    i++;
  }

  printf("In numeric form: %s\n", phone_number);

  return 0;
}
