
#ifndef CHESSENGINE2_NONSLIDERSATTACKS_H
#define CHESSENGINE2_NONSLIDERSATTACKS_H

#include "../definitions/std_typedef.h"
#include "../utils/bitops.h"

void initWhitePawnAttacks();
void initBlackPawnAttacks();
void initWhitePushAttacks();
void initBlackPushAttacks();
void initKnightAttacks();
void initKingAttacks();

extern ull whitePawnAttacks[64];
extern ull blackPawnAttacks[64];
extern ull whitePawnPush[64];
extern ull blackPawnPush[64];
extern ull knightAttacks[64];
extern ull kingAttacks[64];



#endif
