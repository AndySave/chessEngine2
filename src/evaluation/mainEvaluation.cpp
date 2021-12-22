
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


/*
 * Initializes the material value. Must be called after FEN function because it needs
 * board info
 */
void initMaterial(Board *brd){
    for (int pce = P; pce <= k; pce++){
        ull pieces = brd->bitboards[pce];
        int cnt = countBits(pieces);

        if (pce <= K){
            materialMG += cnt * pieceValuesMg[pce];
            materialEG += cnt * pieceValuesEg[pce];
        }else{
            materialMG -= cnt * pieceValuesMg[pce];
            materialEG -= cnt * pieceValuesEg[pce];
        }
    }
}

/*
 * Used to incrementally add material to the material variable
 */
void addMaterial(int piece){
    int color = piece <= K ? white : black;

    if (color == white){
        materialMG += pieceValuesMg[piece];
        materialEG += pieceValuesEg[piece];
    }else{
        materialMG -= pieceValuesMg[piece];
        materialEG -= pieceValuesEg[piece];
    }
}

/*
 * Used to incrementally remove material from the material variable
 */
void removeMaterial(int piece){
    int color = piece <= K ? white : black;

    if (color == white){
        materialMG -= pieceValuesMg[piece];
        materialEG -= pieceValuesEg[piece];
    }else{
        materialMG += pieceValuesMg[piece];
        materialEG += pieceValuesEg[piece];
    }
}



int eval(Board *brd){
    int score = 0;
    int egFactor = (phase * taperedFactor + (totalPhase / 2)) / totalPhase;
    int mgFactor = 256 - egFactor;

    // Adding material to score
    score += (materialMG*mgFactor + materialEG*egFactor) / taperedFactor;

    if (brd->side == white){
        return score;
    }
    return -score;
}

