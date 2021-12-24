#include "main_search.h"

#define maxdepth 32

int ply = 0;
int nodes = 0;
int leafNodes = 0;

int pvLength[64];
int pvTable[64][64];

int searchHistory[12][64];
int searchKillers[2][maxdepth];


bool comp(const Move &lhs, const Move &rhs){
    return lhs.score > rhs.score;
}

int quiescence(Board *brd, int alpha, int beta, SearchInfo *info){
    nodes++;

    // Standing pat (doing nothing). Setting a lower bound on the score which we can do because we can always
    // assume that there is at least one move that can match or beat the lower bound.
    int standPat = eval(brd);
    if (standPat >= beta){ return beta; }
    if (standPat > alpha){ alpha = standPat; }

    Movelist ml;
    generateCaptureMoves(brd, &ml);


    // Sorting moves after score
    sort(ml.moves, ml.moves+ml.count, comp);
    int legal = 0;
    /// -------------SEARCHING STARTS------------- ///
    for (int i = 0; i<ml.count; i++) {
        bool legalMove = makeMove(brd, ml.moves[i].move);
        if (!legalMove){
            continue;
        }

        legal++;
        ply++;
        int value = -quiescence(brd, -beta, -alpha, info);
        undoMove(brd);
        ply--;

        if (value >= beta){
            if (legal == 1){
                info->fhf++;
            }
            info->fh++;
            return beta;
        }
        if (value > alpha){
            alpha = value;
        }
    }

    return alpha;
}

int askMax(Board *brd, int depth, int alpha, int beta, SearchInfo *info) {

    nodes++;

    pvLength[ply] = ply;

    if (brd->fiftyMove == 100) return 0;

    if (depth == 0) {
        leafNodes++;
        return quiescence(brd, alpha, beta, info);
    }

    int side = brd->side;
    Movelist ml;
    generateMoves(brd, &ml);
    int bestmove;


    // If a move in the move list is a pv move, then give it a high score
    int pvMove = pvTable[ply][ply];
    bool foundPvMove = false;
    if (pvMove != 0){
        for (int i = 0; i < ml.count; i++){
            if (ml.moves[i].move == pvMove){
                ml.moves[i].score = 2000000;
                foundPvMove = true;
                break;
            }
        }
    }

    // Sorting moves after score
    sort(ml.moves, ml.moves+ml.count, comp);

    /// -------------SEARCHING STARTS------------- ///
    int legal = 0;
    for (int i = 0; i < ml.count; i++) {
        bool legalMove = makeMove(brd, ml.moves[i].move);
        if (!legalMove) continue;

        legal++;
        ply++;

        int value;
        if (legal == 1 || foundPvMove){
            value = -askMax(brd, depth-1, -beta, -alpha, info);
        }else{
            // Window is closed and we look if we fail high or fail low
            value = -askMax(brd, depth-1, -alpha-1, -alpha, info);
            // If move fails high but is less than beta it is a new best move and
            // we have to do a re-search with full window
            if (value > alpha && value < beta){
                value = max(value, -askMax(brd, depth-1, -beta, -alpha, info));
            }
        }

        undoMove(brd);
        ply--;

        // Move fails hard (Move was too good. Opponent has better option somewhere else in the tree)
        if (value >= beta){
            if (legal == 1){
                info->fhf++;
            }
            info->fh++;
            return beta;
        }

        // Move beat alpha (new best move)
        if (value > alpha){
            foundPvMove = true;
            alpha = value;
            bestmove = ml.moves[i].move;

            pvTable[ply][ply] = bestmove;

            for (int nextPly = ply+1; nextPly < pvLength[ply+1]; nextPly++){
                pvTable[ply][nextPly] = pvTable[ply+1][nextPly];
            }

            pvLength[ply] = pvLength[ply+1];
        }
    }

    if (!legal) {
        if (side == white && isSquareAttacked(brd, brd->whiteKingPos, false)) return -mateScore + ply;
        if (side == black && isSquareAttacked(brd, brd->blackKingPos, true)) return -mateScore + ply;
        return 0;
    }

    return alpha;
}

void search(Board *brd, int depth) {
    memset(pvLength, 0, sizeof(pvLength));
    memset(pvTable, 0, sizeof(pvTable));

    memset(searchHistory, 0, sizeof(searchHistory));
    memset(searchKillers, 0, sizeof(searchKillers));

    SearchInfo info;

    for (int i = 1; i <= depth; i ++) {
        nodes = 0;
        int t1 = getTime();
        int score = askMax(brd, i, -INF, INF, &info);
        int t2 = getTime();
        cout << "D" << i << ": " << "nodes: " << nodes << " leafs: " << leafNodes << " score: " << score << " ordering: " << info.fhf / info.fh << " time: " << t2-t1 << "ms" << '\n';
        cout << "Pv: ";
        for (int ct = 0; ct < pvLength[0]; ct++){
            int move = pvTable[0][ct];
            int fromSq = fromSquare(move);
            int toSq = toSquare(move);
            cout << "d"<< ct+1 << ": " << sqToAlgebraic(fromSq) << sqToAlgebraic(toSq) << " ";
        }
        cout << "\n\n";
    }
}


