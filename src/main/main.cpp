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



int main() {
    initBitMasks();
    initWhitePawnAttacks();
    initBlackPawnAttacks();
    initKnightAttacks();
    initKingAttacks();
    initBishopAttackMasks();
    initRookAttackMasks();

    initHashkeys();

    initMvvLva();

    fillBishopAttacksArray();
    fillRookAttacksArray();


    Board board;
    string fenString = "6k1/5ppp/8/8/8/8/8/1K1R4 w - - 0 1";
    FEN(&board, fenString);
    printBoard(&board);

    // Late inits
    initPhase(&board);
    initMaterial(&board);
    initPieceTable(&board);

    search(&board, 10);
}


