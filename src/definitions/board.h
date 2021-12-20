
#ifndef CHESSENGINE2_BOARD_H
#define CHESSENGINE2_BOARD_H

#include "std_typedef.h"
#include <iostream>
#include "../utils/bitops.h"
#include "../utils/helpers.h"
#include <bitset>


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

void printBoard(Board *brd);
void cleanBoard(Board *brd);

#endif