#include "main_search.h"

bool isCheckmate(Board *brd) {
    if (brd->side == white && isSquareAttacked(brd, brd->whiteKingPos, false)) return true;
    if (brd->side == black && isSquareAttacked(brd, brd->blackKingPos, true)) return true;
    return false;
}

int miniMax(Board *brd, int depth) {
    int side = brd->side;
    Movelist l;
    generateMoves(brd, &l);

    if (l.count <= 0) {
        if (isCheckmate(brd)) { //checkmate
            if (side == white) return -mateScore-depth;
            if (side == black) return mateScore+depth;

        } else { //stalemate
            return 0;
        }
    }

    if (depth == 0) {
        return eval(brd);
    }

    if (side == white) {
        int maxEval = -INF;

        for (int i = 0; i<l.count; i++) {
            int eval = miniMax(brd, depth-1);
            maxEval = max(maxEval, eval);
        }

        return maxEval;

    } else {
        int minEval = INF;

        for (int i = 0; i<l.count; i++) {
            int eval = miniMax(brd, depth-1);
            minEval = min(minEval, eval);
        }

        return minEval;
    }
}