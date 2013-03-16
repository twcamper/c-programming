#ifndef CHESS_H
#define CHESS_H

typedef enum {BLACK = 0, WHITE = 255} Color;
typedef enum {EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING} Piece;


typedef struct { Color color; Piece piece; } Square;

extern Square board[8][8];

void new_board(Square board[][8]);
int piece_value(Piece);
#endif
