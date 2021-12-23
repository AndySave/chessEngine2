#include "main_search.h"

int ply = 0;
int pvLength[64];
int pvTable[64][64];

int searchCounter = 0;


int quiescence(Board *brd, int alpha, int beta){

    searchCounter++;

    int score = eval(brd);

    if (score >= beta){ return beta; }

    if (score > alpha){ alpha = score; }

    Movelist ml;
    generateCaptureMoves(brd, &ml);
    for (int i = 0; i<ml.count; i++) {
        bool legalMove = makeMove(brd, ml.moves[i].move);
        if (!legalMove){
            continue;
        }

        ply++;
        int value = -quiescence(brd, -beta, -alpha);
        undoMove(brd);
        ply--;

        if (value >= beta){ return beta; }
        if (value > alpha){
            alpha = value;
        }
    }

    return alpha;
}

int askMax(Board *brd, int depth, int alpha, int beta) {

    searchCounter++;

    pvLength[ply] = ply;

    if (brd->fiftyMove == 100) return 0;

    if (depth == 0) {
        //return eval(brd);
        return quiescence(brd, alpha, beta);
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
        ply++;
        int value = -askMax(brd, depth-1, -beta, -alpha);
        undoMove(brd);
        ply--;

        if (value >= beta){ return beta; }
        if (value > alpha){
            alpha = value;
            bestmove = ml.moves[i].move;

            pvTable[ply][ply] = bestmove;

            for (int nextPly = ply+1; nextPly < pvLength[ply+1]; nextPly++){
                pvTable[ply][nextPly] = pvTable[ply+1][nextPly];
            }

            pvLength[ply] = pvLength[ply+1];
        }
    }

    if (!existsLegal) {
        if (side == white && isSquareAttacked(brd, brd->whiteKingPos, false)) return -mateScore + ply;
        if (side == black && isSquareAttacked(brd, brd->blackKingPos, true)) return -mateScore + ply;
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
        cout << "Pv: ";
        for (int ct = 0; ct < pvLength[0]; ct++){
            int move = pvTable[0][ct];
            int fromSq = fromSquare(move);
            int toSq = toSquare(move);
            cout << "d"<< ct+1 << ": " << sqToAlgebraic(fromSq) << sqToAlgebraic(toSq) << " ";
        }
        cout << "\n";
    }
}