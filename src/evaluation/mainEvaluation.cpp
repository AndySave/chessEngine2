
#include "mainEvaluation.h"

/*
 * Initializes the phase value. Must be called after FEN function has been called because it
 * needs board info.
 */
void initPhase(Board *brd){
    phase = 0;

    for (int pce = P; pce <= k; pce++){
        if (pce == K || pce == k){ continue; }
        int count = countBits(brd->bitboards[pce]);

        phase += tapered[pce] * count;
    }
}

/*
 * Call whenever a piece gets captured or a new piece gets added to the board i.e. promotion.
 * This function incrementally updates the game phase.
 */
void addPhase(int piece){
    phase += tapered[piece];
}

void removePhase(int piece){
    phase -= tapered[piece];
}

/*
 * Returns an int between 0 and 256. The bigger the value, the later we are in the game.
 * 0 = Opening, 256 = Endgame
 */
int getPhase(){
    return (phase * taperedFactor + (totalPhase / 2)) / totalPhase;
}


/*
 * Initializes the material value. Must be called after FEN function because it needs
 * board info
 */
void initMaterial(Board *brd){
    materialMG = 0;
    materialEG = 0;

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


/*
 * Main eval. Every evaluation function should be in here
 */
int eval(Board *brd){
    int score = 0;

    int mgFactor = getPhase();
    int egFactor = 256 - mgFactor;

    // Adding material to score
    score += (materialMG*mgFactor + materialEG*egFactor) / taperedFactor;

    // Adding piece tables to score
    score += (pieceTableScoreMG*mgFactor + pieceTableScoreEG*egFactor) / taperedFactor;

    // Adding evaluation score of position mobility
    //mobilityEvaluation(brd);
    //score += (midMobility*mgFactor + endMobility*egFactor) / taperedFactor;

    // Giving bonus for passed pawns
    passedPawnEvaluation(brd);
    score += (passedPawnScoreMG*mgFactor + passedPawnScoreEG*egFactor) / taperedFactor;

    // Giving penalty for isolated pawns
    score += isolatedPawnEvaluation(brd);

    // Giving penalty for backwards pawns
    score += backwardsPawnEvaluation(brd);

    // Giving bonus for pawns if they are protected by another pawn
    score += pawnChainEvaluation(brd);

    if (brd->side == white){
        score += tempoBonus;
        return score;
    }
    score -= tempoBonus;
    return -score;
}




