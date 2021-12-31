#include <iostream>
#include "../utils/bitops.h"
#include "../definitions/nonSlidersAttacks.h"
#include "../definitions/slidersAttacks.h"
#include "../definitions/zobristKey.h"
#include "../utils/fen.h"
#include "../definitions/board.h"
#include "../definitions/moveGeneration.h"
#include "../evaluation/mainEvaluation.h"
#include "../evaluation/pieceTables.h"
#include "../search/move_ordering.h"
#include "../search/main_search.h"
#include "../utils/helpers.h"
#include "hashtable.h"
#include "../ui/uci.h"
#include "../evaluation/pawn_structure.h"


int main() {
    initBitMasks();
    initWhitePawnAttacks();
    initBlackPawnAttacks();
    initKnightAttacks();
    initKingAttacks();
    initBishopAttackMasks();
    initRookAttackMasks();

    initWhitePassedPawnMask();
    initBlackPassedPawnMask();
    initIsolatedPawnMasks();
    initBackwardPawnMasks();

    initHashkeys();

    initMvvLva();

    fillBishopAttacksArray();
    fillRookAttacksArray();

    uci();
}



