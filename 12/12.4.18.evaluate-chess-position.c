#include <stdio.h>

#define QUEEN  9
#define ROOK   5
#define BISHOP 3
#define PAWN   1

int black_value(char piece);
int white_value(char piece);
int evaluate_position(char board[8][8]);

int main(void)
{
  char new[8][8] = {
  "rkbqkbkr",
  "pppppppp",
  "        ",
  "        ",
  "        ",
  "        ",
  "PPPPPPPP",
  "RKBQKBKR"
  };
  char advantage_black[8][8] = {
  "rk qkbkr",
  "p p ppp ",
  "b     B ",
  " p      ",
  "  PpP   ",
  "      p ",
  "PP P PP ",
  "RK  KBK "
  };
  char advantage_white[8][8] = {
  " k qk k ",
  "p p ppB ",
  "P R  P  ",
  "       p",
  "  P  K  ",
  "        ",
  " P PP PP",
  " K QKB R"
  };
  int result;
  printf("New game: %d\n", evaluate_position(new));
  result = evaluate_position(advantage_black);
  printf("Advantage black? %d : %d\n", result < 0, result);
  result = evaluate_position(advantage_white);
  printf("Advantage white? %d : %d\n", result > 0, result);

  return 0;
}

int black_value(char piece)
{
  switch(piece) {
    case 'p':
      return PAWN;
    case 'r':
      return ROOK;
    case 'b':
      return BISHOP;
    case 'q':
      return QUEEN;
    default:
      return 0;
  }
}
int white_value(char piece)
{
  switch(piece) {
    case 'P':
      return PAWN;
    case 'R':
      return ROOK;
    case 'B':
      return BISHOP;
    case 'Q':
      return QUEEN;
    default:
      return 0;
  }
}
int evaluate_position(char board[8][8])
{
  int black, white;
  char *sq;
  black = white = 0;
  for (sq = &board[0][0]; sq <= &board[7][7]; sq++) {
    black += black_value(*sq);
    white += white_value(*sq);
  }
  return white - black;
}
