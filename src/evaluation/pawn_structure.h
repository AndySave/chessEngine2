
#ifndef CHESSENGINE2_PAWN_STRUCTURE_H
#define CHESSENGINE2_PAWN_STRUCTURE_H

#include "../utils/bitops.h"
#include "../definitions/std_typedef.h"
#include "../definitions/board.h"
#include "../definitions/nonSlidersAttacks.h"

/// --------------------PASSED PAWN-------------------- ///
// TODO: Temporary. Make more advanced passed pawn handling
inline int passedPawnBonus = 75;

inline ull whitePassedPawnMasks[64];
inline ull blackPassedPawnMasks[64];

void initWhitePassedPawnMask();
void initBlackPassedPawnMask();

bool pawnIsPassed(Board *brd, int sq, int color);
int passedPawnEvaluation(Board *brd);

/// --------------------ISOLATED PAWN-------------------- ///
inline int isolatedPawnPenalty = 50;

inline ull isolatedPawnMasks[64];

void initIsolatedPawnMasks();

bool pawnIsIsolated(Board *brd, int sq, int color);
int isolatedPawnEvaluation(Board *brd);

/// --------------------BACKWARDS PAWN-------------------- ///
inline int backwardsPawnPenalty = 25;

inline ull backwardsPawnMasks[64];

void initBackwardPawnMasks();

bool pawnIsBackwards(Board *brd, int sq, int color);
int backwardsPawnEvaluation(Board *brd);


#endif
