
#include "mainEvaluation.h"

/*
 * Initializes the phase value. Must be called after FEN function has been called because it
 * needs board info.
 */
void initPhase(Board *brd){
    phase = totalPhase;

    for (int pce = P; pce <= k; pce++){
        if (pce == K || pce == k){ continue; }
        int count = countBits(brd->bitboards[pce]);

        phase -= tapered[pce] * count;
    }
}

/*
 * Call whenever a piece gets captured or a new piece gets added to the board i.e. promotion.
 * This function incrementally updates the game phase.
 */
void updatePhase(int piece){
    phase -= tapered[piece];
}

/*
 * Returns an int between 0 and 256. The bigger the value, the later we are in the game.
 * 0 = Opening, 256 = Endgame
 */
int getPhase(){
    return (phase * 256 + (totalPhase / 2)) / totalPhase;
}


void initMaterial(Board *brd){

}



int eval(Board *brd){
    int score = 0;



    if (brd->side == white){
        return score;
    }
    return -score;
}

