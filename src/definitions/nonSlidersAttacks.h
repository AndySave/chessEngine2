
#ifndef CHESSENGINE2_NONSLIDERSATTACKS_H
#define CHESSENGINE2_NONSLIDERSATTACKS_H

#include "../definitions/std_typedef.h"
#include "../utils/bitops.h"

void initWhitePawnAttacks();
void initBlackPawnAttacks();
void initKnightAttacks();
void initKingAttacks();

inline ull whitePawnAttacks[64];
inline ull blackPawnAttacks[64];
inline ull knightAttacks[64];
inline ull kingAttacks[64];



#endif
