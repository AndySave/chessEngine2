
#ifndef CHESSENGINE2_MOVEGENERATION_H
#define CHESSENGINE2_MOVEGENERATION_H

#include "nonSlidersAttacks.h"
#include "board.h"
#include "slidersAttacks.h"
#include "std_typedef.h"
#include <iostream>
#include "moveStructs.h"
#include "move.h"

bool isSquareAttacked(Board *brd, int sq, bool whiteAttacking);
void printAttackedSquares(Board *brd, bool whiteAttacking);

void generateMoves(Board *brd);


#endif
