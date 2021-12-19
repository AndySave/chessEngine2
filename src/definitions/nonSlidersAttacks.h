
#ifndef CHESSENGINE2_NONSLIDERSATTACKS_H
#define CHESSENGINE2_NONSLIDERSATTACKS_H

#include "../definitions/std_typedef.h"

void initPawnAttacks();
void initKnightAttacks();
void initKingAttacks();

inline ull pawnAttacks[64];
inline ull knightAttacks[64];
inline ull kingAttacks[64];



#endif
