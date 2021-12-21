
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

    // Halfmoves since game started
    int ply;
    // Fullmoves since game started
    int move;
    // Halfmoves since last capture or pawn move
    int fiftyMove;

    int whiteKingPos;
    int blackKingPos;

    ull hashKey = 0ull;
};

void printBoard(Board *brd);
void cleanBoard(Board *brd);

#endif