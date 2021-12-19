
#ifndef CHESSENGINE2_SLIDERSATTACKS_H
#define CHESSENGINE2_SLIDERSATTACKS_H

#include "../definitions/std_typedef.h"
#include "../utils/bitops.h"

ull incrementalBishopAttack(int sq);
ull incrementalRookAttack(int sq);

void initBishopAttackMasks();
void initRookAttackMasks();

inline ull bishopAttackMasks[64];
inline ull rookAttackMasks[64];

#endif
