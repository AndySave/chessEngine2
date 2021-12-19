#include <iostream>
#include "../utils/bitops.h"
#include "../definitions/enums.h"
#include "../definitions/nonSlidersAttacks.h"


int main() {

    initBitMasks();
    initPawnAttacks();
    initKnightAttacks();
    initKingAttacks();

    printBitboard(pawnAttacks[d2]);
}

