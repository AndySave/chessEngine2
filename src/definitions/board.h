
#ifndef CHESSENGINE2_BOARD_H
#define CHESSENGINE2_BOARD_H

#include "std_typedef.h"

struct Board{
    ull bitboards[12];
    ull occupancies[3];

    int side;
    int enpassantSq = noSq;
    int castle;

};

#endif