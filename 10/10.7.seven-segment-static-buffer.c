#include <stdio.h>
#include <ctype.h>

#define MAX_DIGITS 10
#define CHARACTER_HEIGHT 3
#define CHARACTER_WIDTH 3
/*
     _       _   _   _   _   _  _   _
|_| |_|   | | | |_    | |_|  _| _| |_
  |  _|   | |_| |_|   | |_| |_  _|  _|

 * An ASCII simulation of a seven-segment character
 * is 3 rows high, 3 columns wide.
 *
 */
const char digit_tables[10][3][3] = {
  {" _ ",
   "| |",
   "|_|"},

  {"   ",
   "  |",
   "  |"},

  {" _ ",
   " _|",
   "|_ "},

  {" _ ",
   " _|",
   " _|"},

  {"   ",
   "|_|",
   "  |"},

  {" _ ",
   "|_ ",
   " _|"},

  {" _ ",
   "|_ ",
   "|_|"},

  {" _ ",
   "  |",
   "  |"},

  {" _ ",
   "|_|",
   "|_|"},

  {" _ ",
   "|_|",
   " _|"}
};

int main(void)
{
  char input[255];
  int row, i, which_digit, digit_count;

  printf("Enter a number up to 10 digits: ");
  fgets(input, sizeof(input), stdin);

  for (row = 0; row < CHARACTER_HEIGHT; row++)  {
    /*
       ignore non-digit characters,
       print up to 10 digits from the input
    */
    for (i = 0, digit_count = 0; input[i] != '\n' && digit_count < MAX_DIGITS; i++) {
      if (isdigit(input[i])) {
        which_digit = (int) input[i] - '0';

        /* print a row (a string) from the digit character's table */
        printf(" %.*s", CHARACTER_WIDTH, digit_tables[which_digit][row]);
        digit_count++;
      }
    }
    printf("\n");
  }
  return 0;
}
