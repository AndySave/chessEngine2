#include "mobility.h"

void mobilityEvaluation(Board *brd) {
    midMobility = 0;
    endMobility = 0;

    initMobility(brd);

    for (int i = 0; i<numOfPieces; i++) {
        int curSq = presentPieces[i];
        int curPiece = pieceOfSquare[curSq];
        int curMobility = mobility[curSq];

        switch (curPiece) {
            case n:
                midMobility -= mobilityBonus[1][curMobility][0];
                endMobility -= mobilityBonus[1][curMobility][1];
                break;
            case b:
                midMobility -= mobilityBonus[2][curMobility][0];
                endMobility -= mobilityBonus[2][curMobility][1];
                break;
            case r:
                midMobility -= mobilityBonus[3][curMobility][0];
                endMobility -= mobilityBonus[3][curMobility][1];
                break;
            case q:
                midMobility -= mobilityBonus[4][curMobility][0];
                endMobility -= mobilityBonus[4][curMobility][1];
                break;
            case N:
                midMobility += mobilityBonus[1][curMobility][0];
                endMobility += mobilityBonus[1][curMobility][1];
                break;
            case B:
                midMobility += mobilityBonus[2][curMobility][0];
                endMobility += mobilityBonus[2][curMobility][1];
                break;
            case R:
                midMobility += mobilityBonus[3][curMobility][0];
                endMobility += mobilityBonus[3][curMobility][1];
                break;
            case Q:
                midMobility += mobilityBonus[4][curMobility][0];
                endMobility += mobilityBonus[4][curMobility][1];
                break;
            default:
                break;
        }
    }
}

