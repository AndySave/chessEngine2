#include "main_search.h"

#define maxdepth 32

int ply = 0;
int nodes = 0;
int leafNodes = 0;

int pvLength[64];
int pvTable[64][64];

int searchHistory[12][64];
int searchKillers[2][maxdepth];

const int fullDepthMoves = 5;
const int reductionLimit = 3;

const int nullMoveReductionLimit = 2;

int aspirationFac = 65;

bool comp(const Move &lhs, const Move &rhs){
    return lhs.score > rhs.score;
}

int quiescence(Board *brd, int alpha, int beta, SearchInfo *info){
    nodes++;

    // Fifty move rule and repetition check
    if (brd->fiftyMove == 100 || isRepetition(brd)){ return 0; }

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

int askMax(Board *brd, int depth, int alpha, int beta, SearchInfo *info, bool doNull) {

    nodes++;

    pvLength[ply] = ply;

    // Fifty move rule and repetition check
    if (brd->fiftyMove == 100 || isRepetition(brd)){ return 0; }

    if (depth == 0) {
        leafNodes++;
        return quiescence(brd, alpha, beta, info);
    }

    int kingPos = brd->side == white ? brd->whiteKingPos : brd->blackKingPos;
    bool inCheck = isSquareAttacked(brd, kingPos, brd->side ^ 1);

    int value;
    if (doNull && !inCheck && depth >= 3 && ply){
        makeNullMove(brd);
        value = -askMax(brd, depth-1-nullMoveReductionLimit, -beta, -beta+1, info, false);
        undoNullMove(brd);

        if (value >= beta){
            return beta;
        }
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

        if (legal == 1 || foundPvMove){
            // Trust the move ordering and do a full search on first move
            value = -askMax(brd, depth-1, -beta, -alpha, info, true);
        }else{
            // If we have searched many moves without a fail high and we are not
            // too close to the root, we do a reduced search
            // TODO: Might not want to do a reduced search if we are in check or if move is a capture
            if (legal >= fullDepthMoves && depth >= reductionLimit){
                value = -askMax(brd, depth-2, -alpha-1, -alpha, info, true);
            }else{
                value = alpha+1;
            }

            if (value > alpha){
                // Window is closed and we look if we fail high or fail low
                value = -askMax(brd, depth-1, -alpha-1, -alpha, info, true);
                // If move fails high but is less than beta it is a new best move and
                // we have to do a re-search with full window
                if (value > alpha && value < beta){
                    value = -askMax(brd, depth-1, -beta, -alpha, info, true);
                }
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
        if  (inCheck){ return -mateScore + ply; }
        return 0;
    }

    return alpha;
}

void search(Board *brd, int maxDepth) {
    memset(pvLength, 0, sizeof(pvLength));
    memset(pvTable, 0, sizeof(pvTable));

    memset(searchHistory, 0, sizeof(searchHistory));
    memset(searchKillers, 0, sizeof(searchKillers));

    SearchInfo info;

    int alpha = -INF, beta = INF;
    int searchTime = 0;
    for (int depth = 1; depth <= maxDepth; depth++) {
        nodes = 0;
        int t1 = getTime();
        int score = askMax(brd, depth, alpha, beta, &info, true);
        int t2 = getTime();
        searchTime += t2-t1;

        if (score <= alpha){
            alpha = -INF;
            depth--;
            continue;
        }

        if (score >= beta){
            beta = INF;
            depth--;
            continue;
        }

        alpha = score - aspirationFac;
        beta = score + aspirationFac;


        cout << "D" << depth << ": " << "nodes: " << nodes << " leafs: " << leafNodes << " score: " << score << " ordering: " << info.fhf / info.fh << " time: " << searchTime << "ms" << '\n';
        cout << "Pv: ";
        for (int ct = 0; ct < pvLength[0]; ct++){
            int move = pvTable[0][ct];
            int fromSq = fromSquare(move);
            int toSq = toSquare(move);
            cout << "d"<< ct+1 << ": " << sqToAlgebraic(fromSq) << sqToAlgebraic(toSq) << " ";
        }
        cout << "\n\n";

        searchTime = 0;
    }
}

