#include "chess.h"

void new_board(Square board[][8])
{
    int rank, file;

    board[0][0] = (Square) {BLACK, ROOK};
    board[0][1] = (Square) {BLACK, KNIGHT};
    board[0][2] = (Square) {BLACK, BISHOP};
    board[0][3] = (Square) {BLACK, QUEEN};
    board[0][4] = (Square) {BLACK, KING};
    board[0][5] = (Square) {BLACK, BISHOP};
    board[0][6] = (Square) {BLACK, KNIGHT};
    board[0][7] = (Square) {BLACK, ROOK};

    for (file = 0; file < 8; file++)
      board[1][file] = (Square) {BLACK, PAWN};

    for (rank = 2; rank < 6; rank++)
      for (file = 0; file < 8; file++)
        board[rank][file] = (Square) {BLACK, EMPTY};

    for (file = 0; file < 8; file++)
      board[6][file] = (Square) {WHITE, PAWN};

    board[7][0] = (Square) {WHITE, ROOK};
    board[7][1] = (Square) {WHITE, KNIGHT};
    board[7][2] = (Square) {WHITE, BISHOP};
    board[7][3] = (Square) {WHITE, QUEEN};
    board[7][4] = (Square) {WHITE, KING};
    board[7][5] = (Square) {WHITE, BISHOP};
    board[7][6] = (Square) {WHITE, KNIGHT};
    board[7][7] = (Square) {WHITE, ROOK};
}
int piece_value(Piece p)
{
  static const int values[] = {0, 1, 3, 3, 5, 9, 200};
  return values[p];
}
