
#ifndef CHESSENGINE2_MOVEGENERATION_H
#define CHESSENGINE2_MOVEGENERATION_H

#include "nonSlidersAttacks.h"
#include "board.h"
#include "slidersAttacks.h"
#include "std_typedef.h"
#include <iostream>
#include "moveStructs.h"
#include "move.h"


void generateMoves(Board *brd, Movelist *lst);
void generateCaptureMoves(Board *brd, Movelist *lst);


#endif
