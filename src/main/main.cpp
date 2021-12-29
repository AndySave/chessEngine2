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
    string fenString = "2r3k1/pbqr1pp1/1p2p2p/2npP2P/1Rp3Q1/2P1BPP1/2P1P1B1/3R2K1 w - - 10 36";
    fenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    FEN(&board, fenString);
    printBoard(&board);

    // Late inits
    initPhase(&board);
    initMaterial(&board);
    initPieceTable(&board);


    search(&board, 20);
}




