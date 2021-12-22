#ifndef CHESSENGINE2_MAIN_SEARCH_H
#define CHESSENGINE2_MAIN_SEARCH_H

#include "../utils/bitops.h"
#include "../definitions/nonSlidersAttacks.h"
#include "../definitions/slidersAttacks.h"
#include "../definitions/zobristKey.h"
#include "../utils/fen.h"
#include "../definitions/board.h"
#include "../definitions/moveGeneration.h"
#include "../evaluation/mainEvaluation.h"
#include "../evaluation/pieceTables.h"

#define INF 1000000000
#define mateScore 1000000

struct SearchInfo{
    int startTime;
    int stopTime;
    int depth;
    int depthSet;
    int timeSet;
    int movesToGo;
    int infinite;

    long long nodes;

    bool quit;
    bool stopped;

    float fh;
    float fhf;
};

int miniMax(Board *brd, int depth);


#endif //CHESSENGINE2_MAIN_SEARCH_H
