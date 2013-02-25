#include <stdio.h>
#include <ctype.h>

#define MAX_DIGITS 10
#define NO_SEGMENT -1
char input[255];

void print_segment(int segment, int digit);
void print_row(int s1, int s2, int s3);

int main(void)
{

  printf("Enter a number up to %d digits: ", MAX_DIGITS);
  fgets(input, sizeof(input), stdin);

  /* top row of all characters: only segment 0 is possible */
  print_row(NO_SEGMENT, 0, NO_SEGMENT);

  /* middle row of all characters: segments 5, 6, and 1 are possible */
  print_row(5, 6, 1);

  /* bottom row of all characters: segments 4, 3 and 2 are possible */
  print_row(4, 3, 2);

  return 0;
}
void print_segment(int segment, int digit)
{
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
  const int segments[10][7] = {
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
  const char display[7] = "_||_||_";

  if (segment >= 0 && segments[digit][segment])
    printf("%c", display[segment]);
  else
    printf(" ");
}
void print_row(int s1, int s2, int s3)
{
  int i, which_digit, digit_count;

  for (i = 0, digit_count = 0; input[i] != '\n' && digit_count < MAX_DIGITS; i++) {
    if (isdigit(input[i])) {
      which_digit = (int) input[i] - '0';
      print_segment(s1, which_digit);
      print_segment(s2, which_digit);
      print_segment(s3, which_digit);
      printf(" ");

      digit_count++;
    }
  }
  printf("\n");
}
