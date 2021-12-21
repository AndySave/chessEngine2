
#include "mainEvaluation.h"


int pceScore[12] = {1, 3, 3, 5, 9, 100, 1, 3, 3, 5, 9, 100};
int material(Board *brd){
    int score = 0;

    for (int pce = P; pce <= K; pce++){
        score += countBits(brd->bitboards[pce]) * pceScore[pce];
    }

    for (int pce = p; pce <= k; pce++){
        score -= countBits(brd->bitboards[pce]) * pceScore[pce];
    }

    return score;
}


int eval(Board *brd){
    int score = 0;

    score += material(brd);

    if (brd->side == white){
        return score;
    }
    return -score;
}

