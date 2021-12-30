
#ifndef CHESSENGINE2_PAWN_STRUCTURE_H
#define CHESSENGINE2_PAWN_STRUCTURE_H

#include "../utils/bitops.h"
#include "../definitions/std_typedef.h"
#include "../definitions/board.h"


inline ull whitePassedPawnMasks[64];
inline ull blackPassedPawnMasks[64];

void initWhitePassedPawnMask();
void initBlackPassedPawnMask();

bool pawnIsPassed(Board *brd, int sq, int color);


#endif
