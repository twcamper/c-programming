#include <stdio.h>

int main(void)
{
  int n, size, i, new_row, new_col;
  int row, col;

  printf("This program creates a magic square of a specified size.\nThe size must be an odd number between 1 and 99\n");
  printf("Enter the size of the magic square: ");
  scanf("%d", &n);

  /*validate input*/
  if ((n % 2) == 0 || n < 1 || n > 99)  {
    fprintf(stderr, "Enter an ODD number between 1 and 99\n");
    return 1;
  }

  int square[n][n];

  /*initialize to all zeroes*/
  for (row = 0; row < n; row++) {
    for (col = 0; col < n; col++)
      square[row][col] = 0;
  }

  /*Start by placing the number 1 in the middle of row 0*/
  row = 0;
  col = n / 2;

  size = n * n;
  for (i = 1; i <= size; i++) {
    square[row][col] = i;
    /*
     * Find the new element
     */
    new_row = row;
    new_col = col;

    /*wrap around by resetting the row if necessary*/
    if (new_row == 0)
      new_row = n;
    /*move up by 1*/
    new_row--;

    /*wrap around by resetting the column if necessary*/
    if (new_col ==  n - 1)
      new_col = -1;
    /*move to the right by 1*/
    new_col++;

    /* is the new element available? */
    if (square[new_row][new_col] == 0) {
      row = new_row;
      col = new_col;
    } else {
      /*
       * if the element is already occupied, put the number directly below
       * the previously stored number
       */
      if (row == n - 1)
        row = - 1;
      /*move down by 1*/
      row++;
    }
  }

  for (row = 0; row < n; row++) {
    for (col = 0; col < n; col++)
      printf("%d\t", square[row][col]);
    printf("\n");
  }

  return 0;
}
