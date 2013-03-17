#include "chess.h"
#include "test_runner.h"

int new_board_test(void)
{
  Square board[8][8];
  new_board(board);

  _assert(board[0][0].color == BLACK);
  _assert(board[0][0].piece == ROOK);

  _assert(board[0][3].color == BLACK);
  _assert(board[0][3].piece == QUEEN);

  _assert(board[1][6].color == BLACK);
  _assert(board[1][6].piece == PAWN);

  _assert(board[5][2].color == BLACK);
  _assert(board[5][2].piece == EMPTY);

  _assert(board[6][5].color == WHITE);
  _assert(board[6][5].piece == PAWN);

  _assert(board[7][4].color == WHITE);
  _assert(board[7][4].piece == KING);

  _assert(board[7][7].color == WHITE);
  _assert(board[7][7].piece == ROOK);
  return 0;
}

int piece_value_test(void)
{
  _assert(piece_value(PAWN)    > piece_value(EMPTY));
  _assert(piece_value(KNIGHT)  > piece_value(PAWN));
  _assert(piece_value(BISHOP) == piece_value(KNIGHT));
  _assert(piece_value(ROOK)    > piece_value(BISHOP));
  _assert(piece_value(QUEEN)   > piece_value(ROOK));
  _assert(piece_value(KING)    > piece_value(QUEEN));

  return 0;
}
int all_tests(void)
{
  _run(new_board_test);
  _run(piece_value_test);
  return 0;
}
