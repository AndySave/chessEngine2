#include "main_search.h"

#define maxdepth 32

int ply = 0;
int nodes = 0;
int leafNodes = 0;

const int fullDepthMoves = 5;
const int reductionLimit = 3;

constexpr int nullMoveReductionLimit = 3;

constexpr int aspirationFac = 65;

void checkIfStopped(SearchInfo *info){
    if (getTime() > info->stopTime){
        info->stopped = true;
    }
}

int quiescence(Board *brd, int alpha, int beta, SearchInfo *info){
    nodes++;

    if ((nodes & 2047) == 0){
        checkIfStopped(info);
    }
    if (info->stopped){
        return 0;
    }

    // Fifty move rule and repetition check
    if (isRepetition(brd)){ return 0; }

    // Standing pat (doing nothing). Setting a lower bound on the score which we can do because we can always
    // assume that there is at least one move that can match or beat the lower bound.
    int standPat = eval(brd);
    if (standPat >= beta){ return beta; }
    // Delta pruning
    // TODO: Turn off in endgame
    int bigDelta = 1000;  // Value of a rook
    if (standPat < alpha - bigDelta){
        return alpha;
    }
    if (standPat > alpha){ alpha = standPat; }

    Movelist ml;
    generateCaptureMoves(brd, &ml);

    // Sorting moves after score
    sortMoves(&ml);

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

int askMax(Board *brd, int depth, int alpha, int beta, SearchInfo *info, HashTable *tt, bool doNull) {
    nodes++;

    if ((nodes & 2047) == 0){
        checkIfStopped(info);
    }
    if (info->stopped){
        return 0;
    }

    // Fifty move rule and repetition check
    if (isRepetition(brd)){ return 0; }

    int value = -INF;
    int bestmove = 0;
    if (probeHashTable(brd, tt, &bestmove, &value, alpha, beta, depth)){
        tt->cut++;
        return value;
    }

    if (depth == 0) {
        leafNodes++;
        return quiescence(brd, alpha, beta, info);
    }

    int hashFlag = hashAlpha;

    int kingPos = brd->side == white ? brd->whiteKingPos : brd->blackKingPos;
    bool inCheck = isSquareAttacked(brd, kingPos, brd->side);

    // Check extension (Search deeper if king in check)
    if (inCheck && brd->ply < info->depthMax){
        depth++;
    }

    // Null move pruning
    if (doNull && depth >= nullMoveReductionLimit && !inCheck && ply){
        makeNullMove(brd);
        value = -askMax(brd, depth-nullMoveReductionLimit, -beta, -beta+1, info, tt, false);
        undoNullMove(brd);

        if (value >= beta){
            return beta;
        }
    }

    // Razoring
    if (!inCheck && depth <= 3){
        value = eval(brd) + 125;

        int newValue;
        if (value < beta){
            if (depth == 1){
                newValue = quiescence(brd, alpha, beta, info);

                if (newValue > value){
                    return newValue;
                }
                return value;
            }
        }

        value += 175;

        if (value < beta && depth <= 2){
            newValue = quiescence(brd, alpha, beta, info);

            if (newValue < beta){
                if (newValue > value){
                    return newValue;
                }
                return value;
            }
        }
    }

    Movelist ml;
    generateMoves(brd, &ml);

    // If a move in the move list is a pv move, then give it a high score
    if (bestmove != 0){
        for (int i = 0; i < ml.count; i++){
            if (ml.moves[i].move == bestmove){
                ml.moves[i].score = 2000000;
                break;
            }
        }
    }

    // Sorting moves after score
    sortMoves(&ml);

    /// -------------SEARCHING STARTS------------- ///
    int legal = 0;
    for (int i = 0; i < ml.count; i++) {
        bool legalMove = makeMove(brd, ml.moves[i].move);
        if (!legalMove) continue;

        legal++;
        ply++;

        if (legal == 1){
            // Trust the move ordering and do a full search on first move
            value = -askMax(brd, depth-1, -beta, -alpha, info, tt, true);
        }else{
            // If we have searched many moves without a fail high and we are not
            // too close to the root, we do a reduced search
            // TODO: Might not want to do a reduced search if we are in check or if move is a capture

            if (legal >= fullDepthMoves && depth >= reductionLimit){
                value = -askMax(brd, depth-2, -alpha-1, -alpha, info, tt, true);
            }else{
                value = alpha+1;
            }

            if (value > alpha){
                // Window is closed and we look if we fail high or fail low
                value = -askMax(brd, depth-1, -alpha-1, -alpha, info, tt, true);
                // If move fails high but is less than beta it is a new best move and
                // we have to do a re-search with full window
                if (value > alpha && value < beta){
                    value = -askMax(brd, depth-1, -beta, -alpha, info, tt, true);
                }
            }
        }

        undoMove(brd);
        ply--;

        // Move beat alpha (new best move)
        if (value > alpha){
            alpha = value;
            bestmove = ml.moves[i].move;

            if (getCaptured(ml.moves[i].move) == noPiece){
                brd->searchHistory[getPiece(bestmove)][toSquare(bestmove)] += depth;
            }

            hashFlag = hashExact;

            // Move fails hard (Move was too good. Opponent has better option somewhere else in the tree)
            if (value >= beta){
                if (legal == 1){
                    info->fhf++;
                }
                info->fh++;

                // Update killer heuristics
                if (getCaptured(ml.moves[i].move) == noPiece){
                    brd->searchKillers[1][brd->ply] = brd->searchKillers[0][brd->ply];
                    brd->searchKillers[0][brd->ply] = ml.moves[i].move;
                }

                storeHash(brd, tt, bestmove, beta, hashBeta, depth);

                return beta;
            }
        }
    }

    if (!legal) {
        if (inCheck){ return -mateScore + ply; }
        return 0;
    }

    storeHash(brd, tt, bestmove, alpha, hashFlag, depth);

    return alpha;
}

void search(Board *brd, HashTable *tt, SearchInfo *info, int maxDepth) {
    // Clearing searchkillers table
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 64; j++){
            brd->searchKillers[i][j] = 0;
        }
    }
    // Clearing history table
    for (int i = 0; i < 12; i++){
        for (int j = 0; j < 64; j++){
            brd->searchHistory[i][j] = 0;
        }
    }

    int alpha = -INF, beta = INF;
    int searchTime = 0;
    int previousBestMove = 0;
    for (int depth = 1; depth <= maxDepth; depth++) {
        info->depthMax = depth+3;
        nodes = 0;
        int t1 = getTime();
        int score = askMax(brd, depth, alpha, beta, info, tt, true);
        int t2 = getTime();
        searchTime += t2-t1;

        checkIfStopped(info);

        if (info->stopped){
            storeHash(brd, tt, previousBestMove, 0, hashExact, 10);
            return;
        }

        previousBestMove = probePvMove(brd, tt);

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

        cout << "info string ";
        cout << "D" << depth << ": ";
        cout << "nodes: " << nodes;
        cout << " leafs: " << leafNodes;
        cout << " score: " << score;
        cout << " ordering: " << info->fhf / info->fh;
        cout << " time: " << searchTime << "ms ";
        cout << "Pv: ";
        int total = getPvLine(brd, tt, depth);
        for (int ct = 0; ct < total; ct++){
            int move = brd->pvTable[ct];
            int fromSq = fromSquare(move);
            int toSq = toSquare(move);
            cout << "d"<< ct+1 << ": " << sqToAlgebraic(fromSq) << sqToAlgebraic(toSq) << " ";
        }
        cout << "\n";

        searchTime = 0;
    }
}



