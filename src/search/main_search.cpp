#include "main_search.h"


int searchCounter = 0;
int askMax(Board *brd, int depth, int alpha, int beta) {
    if (brd->fiftyMove == 100) return 0;

    if (depth == 0) {
        searchCounter++;
        return eval(brd);
    }

    int side = brd->side;
    Movelist ml;
    generateMoves(brd, &ml);

    bool existsLegal = false;
    for (int i = 0; i<ml.count; i++) {
        bool legalMove = makeMove(brd, ml.moves[i].move);
        if (!legalMove) continue;

        existsLegal = true;
        alpha = max(alpha, -askMax(brd, depth-1, -beta, -alpha));
        undoMove(brd);

        if (alpha >= beta) break;
    }

    if (!existsLegal) {
        if (side == white && isSquareAttacked(brd, brd->whiteKingPos, false)) return -mateScore - depth;
        if (side == black && isSquareAttacked(brd, brd->blackKingPos, true)) return -mateScore - depth;
        return 0;
    }

    return alpha;
}

void search(Board *brd, int depth) {
    for (int i = 1; i <= depth; i ++) {
        searchCounter = 0;
        int score = askMax(brd, i, -INF, INF);
        cout << "D" << i << ": " << searchCounter << "\n";
        cout << "Score: " << score << "\n";
        cout << "\n";
    }
}