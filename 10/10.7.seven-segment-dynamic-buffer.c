#include <stdio.h>
#include <ctype.h>
/*
     _       _   _   _   _   _  _   _
|_| |_|   | | | |_    | |_|  _| _| |_
  |  _|   | |_| |_|   | |_| |_  _|  _|

 * An ASCII simulation of a seven-segment character
 * is 3 rows high, 3 columns wide.
 */

/*
 Segment Numbering:

        0
       ---
     5|   |1
      | 6 |
       ---
     4|   |2
      | 3 |
       ---
*/
const int segments_per_character[10][7] = {
  {1, 1, 1, 1, 1, 1, 0},  // 0
  {0, 1, 1, 0, 0, 0, 0},  // 1
  {1, 1, 0, 1, 1, 0, 1},  // 2
  {1, 1, 1, 1, 0, 0, 1},  // 3
  {0, 1, 1, 0, 0, 1, 1},  // 4
  {1, 0, 1, 1, 0, 1, 1},  // 5
  {1, 0, 1, 1, 1, 1, 1},  // 6
  {1, 1, 1, 0, 0, 0, 0},  // 7
  {1, 1, 1, 1, 1, 1, 1},  // 8
  {1, 1, 1, 1, 0, 1, 1}   // 9
};

/* segment position in a 3x3 grid */
const int segment_coordinates[7][2] = {
  {0,1},
  {1,2},
  {2,2},
  {2,1},
  {2,0},
  {1,0},
  {1,1}
};
#define CHAR_HEIGHT 3
#define CHAR_WIDTH  4
#define MAX_DIGITS 34
#define COLUMNS (CHAR_WIDTH * MAX_DIGITS)
char digits[CHAR_HEIGHT][COLUMNS];

void clear_digits_array(void);
void process_digit(int digit, int position);
void print_digits_array(int row_size);

int main(void)
{
  char ch;
  int digit_count = 0;

  clear_digits_array();

  printf("Enter a string with up to %d digits: ", MAX_DIGITS);

  while ((ch = getchar()) != '\n' && digit_count < MAX_DIGITS) {
    if (isdigit(ch)) {
      /* convert the char to an int */
      /* calculate the offset into the output buffer */
      process_digit((int) ch - '0', CHAR_WIDTH * digit_count);
      digit_count++;
    }
  }

  print_digits_array(digit_count * CHAR_WIDTH);
  return 0;
}

void clear_digits_array(void)
{
  for (int row = 0; row < CHAR_HEIGHT; row++)
    for (int col = 0; col < COLUMNS; digits[row][col++] = ' ');
}
void process_digit(int digit, int position)
{
  const char display[7] = {'_', '|', '|', '_', '|', '|', '_'};
  int row, col;

  for (int segment = 0; segment < 7; segment++) {
    if (segments_per_character[digit][segment])  {
      row = segment_coordinates[segment][0];
      col = segment_coordinates[segment][1] + position;
      digits[row][col] = display[segment];
    }
  }
}
void print_digits_array(int row_size)
{
  for (int row = 0; row < CHAR_HEIGHT; row++)
    printf("%.*s\n", row_size, digits[row]);
}
