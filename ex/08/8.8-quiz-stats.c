#include <stdio.h>
#define STUDENTS 5
#define QUIZES 5
#define NEWLINE printf("\n")

int main(void)
{
  int table[STUDENTS][QUIZES] = {{0}};
  int row, col, score, total, low, high;

  printf("Enter quiz scores:\n");
  for (row = 0; row < STUDENTS; row++) {
    printf("Student %d: ", row + 1);
    for (col = 0; col < QUIZES; col++)
      scanf("%d", &table[row][col]);
  }

  NEWLINE;
  printf("Student Stats:\tAverage\tTotal\n");
  for (row = 0; row < STUDENTS; row++) {
    printf("Student %d:", row + 1);
    total = 0;
    for (col = 0; col < QUIZES; col++) {
      total += table[row][col];
    }
    printf("\t%4d\t%4d\n", total / QUIZES, total);
  }
  NEWLINE;

  printf("Quiz Stats:\tLow\tHigh\tAverage\n");
  for (col = 0; col < QUIZES; col++) {
    printf("Quiz %d:\t", col + 1);
    total = 0;
    high = 0;
    low = 100;
    for (row = 0; row < STUDENTS; row++) {
      score = table[row][col];
      if (score > high)
        high = score;
      if (score < low)
        low = score;
      total += score;
    }
    printf("\t%4d\t%4d\t%4d\n", low, high, total / STUDENTS);
  }
  NEWLINE;

  return 0;
}
