#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROWS 15
#define COLS 15
#define MOVES 4

void generate_random_walk(char table[][COLS]);
void print_table(char table[][COLS]);

int main(void)
{
  char table[ROWS][COLS];
  generate_random_walk(table);
  print_table(table);
  return 0;
}

void generate_random_walk(char table[][COLS])
{
  enum { UP, DOWN, LEFT, RIGHT };

  const char available = '.';
  int move, letter, row, col;
  bool possible[4];

  /* using rand() to get the next move */
  srand((unsigned) time(NULL));

  /*
   * pre-fill table with dots
   */
  for (row = 0; row < ROWS; row++) {
    for (col = 0; col < COLS; col++)
      table[row][col] = available;
  }

  /* 
   * Walk the table, populating available cells with successive letters of
   * the alphabet.
   * Each next move is selected randomly from the current possible moves.
   * Break out of the walking loop early if we get boxed in.
   *
   */
  row = col = ROWS / 2;
  for (letter = 0; letter < 26; letter++)  {
    /*make the next move, advancing through the ASCII table in the uppercase range*/
    table[row][col] = 'A' + letter;

    /*
     * determine possible moves
     */
    for (move = 0; move < MOVES; move++)
      possible[move] = false;

    if (row > 0 && table[row-1][col] == available)
      possible[UP] = true;

    if (row < ROWS-1 && table[row+1][col] == available)
      possible[DOWN] = true;

    if (col > 0 && table[row][col-1] == available)
      possible[LEFT] = true;

    if (col < COLS-1 && table[row][col+1] == available)
      possible[RIGHT] = true;

    /*
     * exit if there are no possible moves
     */
    for (move = 0; possible[move] == false && move < MOVES; move++);

    /*no 'true' values were found*/
    if (move == MOVES)
      break;

    /*
     * get next move from the possible ones
     */
    move = -1;
    while (move < 0) {
      move = rand() % MOVES;
      if (possible[move])
        break;
      move = -1;
    }

    /*
     * set up the next move
     */
    switch(move) {
      case UP:
        row--;
        break;
      case DOWN:
        row++;
        break;
      case LEFT:
        col--;
        break;
      case RIGHT:
        col++;
        break;
    }
  }  /* END for each letter */
}

void print_table(char table[][COLS])
{
  int row, col;

  for (row = 0; row < ROWS; row++) {
    for (col = 0; col < COLS; col++)  {
      printf("%2c", table[row][col]);
    }
    printf("\n");
  }
}
