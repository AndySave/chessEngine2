#include "main_search.h"


int quiescence(Board *brd, int alpha, int beta){
    int score = eval(brd);

    if (score >= beta){
        return beta;
    }

    if (score > alpha){ alpha = score; }

    Movelist ml;
    generateCaptureMoves(brd, &ml);
    int bestmove = 0;
    int oldAlpha = alpha;
    bool existsLegal = false;
    for (int i = 0; i<ml.count; i++) {
        bool legalMove = makeMove(brd, ml.moves[i].move);
        if (!legalMove) continue;

        existsLegal = true;
        int value = -quiescence(brd, -beta, -alpha);
        undoMove(brd);

        if (value >= beta){ return beta; }
        if (value > alpha){
            alpha = value;
            bestmove = ml.moves[i].move;
        }
    }

    if (alpha > oldAlpha){

    }


    return alpha;
}

int searchCounter = 0;
int askMax(Board *brd, int depth, int alpha, int beta) {
    if (brd->fiftyMove == 100) return 0;

    if (depth == 0) {
        searchCounter++;
        return quiescence(brd, -beta, -alpha);
    }

    int side = brd->side;
    Movelist ml;
    generateMoves(brd, &ml);
    int oldAlpha = alpha;
    int bestmove = 0;

    bool existsLegal = false;
    for (int i = 0; i<ml.count; i++) {
        bool legalMove = makeMove(brd, ml.moves[i].move);
        if (!legalMove) continue;

        existsLegal = true;
        int value = -askMax(brd, depth-1, -beta, -alpha);
        undoMove(brd);

        if (value >= beta){ return beta; }
        if (value > alpha){
            alpha = value;
            bestmove = ml.moves[i].move;
        }
    }

    if (!existsLegal) {
        if (side == white && isSquareAttacked(brd, brd->whiteKingPos, false)) return -mateScore + depth;
        if (side == black && isSquareAttacked(brd, brd->blackKingPos, true)) return -mateScore + depth;
        return 0;
    }

    if (alpha > oldAlpha){

    }

    return alpha;
}

void search(Board *brd, int depth) {
    for (int i = 1; i <= depth; i ++) {
        searchCounter = 0;
        int score = askMax(brd, i, -INF, INF);
        cout << "D" << i << ": " << searchCounter << "\n";
        cout << "Score: " << score << "\n";
        cout << "Pv: ";

        cout << "\n";
    }
}
