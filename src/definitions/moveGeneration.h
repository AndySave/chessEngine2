
#ifndef CHESSENGINE2_MOVEGENERATION_H
#define CHESSENGINE2_MOVEGENERATION_H

#include "nonSlidersAttacks.h"
#include "board.h"
#include "slidersAttacks.h"
#include "std_typedef.h"
#include <iostream>

bool isSquareAttacked(Board *brd, int sq, bool whiteAttacking);
void printAttackedSquares(Board *brd, bool whiteAttacking);


#endif
