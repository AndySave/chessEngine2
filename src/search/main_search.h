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
#include "../definitions/moveStructs.h"
#include "../utils/helpers.h"
#include <cstring>
#include <algorithm>


#define INF 1000000000
#define mateScore 1000000


struct SearchInfo{
    int startTime;
    int stopTime;
    int depth;
    int depthMax;
    int timeSet;
    int movesToGo;
    int infinite;

    long long nodes;

    bool quit;
    bool stopped;

    float fh;
    float fhf;
};

void search(Board *brd, int maxDepth);

extern int nodes;


#endif //CHESSENGINE2_MAIN_SEARCH_H
