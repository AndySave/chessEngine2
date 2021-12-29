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

    string fenString = "8/5r1k/1Rb5/1p1pB1R1/pP1P4/P2P2K1/2r5/8 w - - 37 77";
    //fenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    FEN(&board, fenString);
    printBoard(&board);

    HashTable tt{};
    initHashTable(&tt);

    // Late inits
    initPhase(&board);
    initMaterial(&board);
    initPieceTable(&board);


    search(&board, &tt, 17);
    search(&board, &tt, 17);
}


