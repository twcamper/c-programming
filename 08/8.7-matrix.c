#include <stdio.h>
#define ROWS 5
#define COLS 5
#define NEWLINE printf("\n")

int main(void)
{
  int table[ROWS][COLS] = {{0}};
  int row, col, total;

  for (row = 0; row < ROWS; row++) {
    printf("Enter row %d: ", row + 1);
    for (col = 0; col < COLS; col++)
      scanf("%d", &table[row][col]);
  }

  NEWLINE;
  printf("Row Totals:\t");
  for (row = 0; row < ROWS; row++) {
    total = 0;
    for (col = 0; col < COLS; col++) {
      total += table[row][col];
    }
    printf(" %5d", total);
  }
  NEWLINE;

  printf("Column Totals:\t");
  for (col = 0; col < COLS; col++) {
    total = 0;
    for (row = 0; row < ROWS; row++) {
      total += table[row][col];
    }
    printf(" %5d", total);
  }
  NEWLINE;

  return 0;
}
