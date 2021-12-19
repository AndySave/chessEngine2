#include <iostream>
#include "../utils/bitops.h"
#include "../definitions/enums.h"
#include "../definitions/nonSlidersAttacks.h"
#include "../definitions/slidersAttacks.h"


int main() {

    initBitMasks();
    initPawnAttacks();
    initKnightAttacks();
    initKingAttacks();
    initBishopAttackMasks();
    initRookAttackMasks();

    for (int sq = 0; sq < 64; sq++){
        printBitboard(rookAttackMasks[sq]);
    }
}


