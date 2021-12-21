
#ifndef CHESSENGINE2_MOVESTRUCTS_H
#define CHESSENGINE2_MOVESTRUCTS_H

#include "std_typedef.h"

/*
 * A move consists of 16 bits:
 * Bits [1, 2] : Special move flag. 00 = nothing, 01 = promotion, 10 = en passant, 11 = castling
 * Bits [3, 4] : Promoted piece. 00 = knight, 01 = bishop, 10 = rook, 11 = queen
 * Bits [5, 10]: To square. Square piece is being moved to. Value from 0-63 inclusive.
 * Bits [11,16]: From square. Square piece is being moved from. Value from 0-63 inclusive.
 */
struct Move {
    unsigned short move; //The move
    int score;
};

struct Movelist{
    Move moves[512];
    int count;
};

struct Undo{
    int move;
    int castlePerm;
    int enPas;
    int fiftyMove;
    ull posKey;
};


#endif
