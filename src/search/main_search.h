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
#include "hash_table.h"
#include <cstring>
#include <algorithm>


#define INF 100001
#define mateScore 100000


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


static inline void sortMoves(Movelist *moves){
    for (int currentMove = 0; currentMove < moves->count; currentMove++){
        for (int nextMove = currentMove+1; nextMove < moves->count; nextMove++){
            if (moves->moves[currentMove].score < moves->moves[nextMove].score){
                swap(moves->moves[currentMove], moves->moves[nextMove]);
            }
        }
    }
}


void search(Board *brd, int maxDepth);

extern int nodes;


#endif //CHESSENGINE2_MAIN_SEARCH_H
