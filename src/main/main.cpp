#include <iostream>
#include "../utils/bitops.h"
#include "../definitions/nonSlidersAttacks.h"
#include "../definitions/slidersAttacks.h"
#include "../definitions/zobristKey.h"
#include "../utils/fen.h"
#include "../definitions/board.h"
#include "../definitions/moveGeneration.h"
#include "../definitions/move.h"


int main() {

    initBitMasks();
    initWhitePawnAttacks();
    initBlackPawnAttacks();
    initKnightAttacks();
    initKingAttacks();
    initBishopAttackMasks();
    initRookAttackMasks();
    initHashkeys();

    fillBishopAttacksArray();
    fillRookAttacksArray();


    Board board;
    string fenString = "8/7k/8/8/4p3/8/3P4/K7 w - - 0 1";
    FEN(&board, fenString);
    printBoard(&board);
    generateMoves(&board);
}





