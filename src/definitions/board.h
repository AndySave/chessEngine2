
#ifndef CHESSENGINE2_BOARD_H
#define CHESSENGINE2_BOARD_H

#include "std_typedef.h"

struct Board{
    ull bitboards[12];
    ull occupancies[3];

    int side;
    int enpassantSq = noSq;
    int castle;

    // Ply is halfmoves since last capture or pawn move
    int ply;
    // Move is fullmoves since game started 
    int move;

    ull hashKey = 0ull;
};

#endif