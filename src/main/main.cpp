#include <iostream>
#include "../utils/bitops.h"
#include "../definitions/nonSlidersAttacks.h"
#include "../definitions/slidersAttacks.h"
#include "../definitions/zobristKey.h"
#include "../utils/fen.h"
#include "../definitions/board.h"
#include "../definitions/moveGeneration.h"
#include "../evaluation/mainEvaluation.h"


long long count = 0;
long long totCount = 0;

void perftRec(Board* brd, int depth) {
    if (depth <= 0) { // Base case
        count++;
        totCount++;
        return;
    }

    Movelist* moveList = new Movelist;
    generateMoves(brd, moveList);

    for (int i = 0 ; i<moveList->count; i++) {
        bool legalMove = makeMove(brd, moveList->moves[i].move);
        if (legalMove) {
            perftRec(brd, depth-1);
            undoMove(brd);
        }
    }
}

void perft(Board* brd, int depth) {
    Movelist l;
    generateMoves(brd, &l);

    for (int i = 0; i<l.count; ++i) {
        makeMove(brd, l.moves[i].move);
        perftRec(brd, depth-1);
        undoMove(brd);
        cout << i+1 << ", " << count << "\n";
        printMove(l.moves[i]);
        cout << "\n\n";
        count =  0;
    }

    cout << totCount << endl;
}

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
    string fenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    FEN(&board, fenString);
    printBoard(&board);

    //makeMove(&board, createMove(b2, b3, 0, noFlag));
    //makeMove(&board, createMove(e7, e5, 0, noFlag));

    perft(&board, 6);
    //cout << count << endl;
}
