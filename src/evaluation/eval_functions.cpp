#include "eval_functions.h"

void mobilityEval(Board* brd) {
    kingSafetyEval = 0;
    midMobilityEval = 0;
    endMobilityEval = 0;

    int whiteKingScore = 0;
    int blackKingScore = 0;

    //WHITE

    //Knight
    ull wKnightPositions = brd->bitboards[N];
    while (wKnightPositions) {
        int curKnight = getLSB(wKnightPositions);
        clearBit(wKnightPositions, curKnight);

        //Non-white squares attacked
        ull knightMobility = knightAttacks[curKnight] & (~brd->occupancies[white]);
        int knightMobilityCount = countBits(knightMobility);

        //Mobility evaluation
        midMobilityEval += mobilityBonus[1][knightMobilityCount][0];
        endMobilityEval += mobilityBonus[1][knightMobilityCount][1];

        //King safety evaluation
        int bKingZoneAttacks = countBits(blackKingZones[brd->blackKingPos] & knightAttacks[curKnight]);
        whiteKingScore += bKingZoneAttacks * attackUnits[N];
    }

    // Bishop
    ull wBishopPositions = brd->bitboards[B];
    while (wBishopPositions) {
        int curBishop = getLSB(wBishopPositions);
        clearBit(wBishopPositions, curBishop);
        ull bishopMobility = bishopAttackRay(brd->occupancies[both], curBishop) & (~brd->occupancies[white]);
        int bishopMobilityCount = countBits(bishopMobility);

        // Mobility evaluation
        midMobilityEval += mobilityBonus[2][bishopMobilityCount][0];
        endMobilityEval += mobilityBonus[2][bishopMobilityCount][1];

        // King safety evaluation
        int bKingZoneAttacks = countBits(blackKingZones[brd->blackKingPos] & bishopAttackRay(brd->occupancies[both], curBishop));
        whiteKingScore += bKingZoneAttacks * attackUnits[B];
    }

    //Rook
    ull wRookPositions = brd->bitboards[R];
    while (wRookPositions) {
        int curRook = getLSB(wRookPositions);
        clearBit(wRookPositions, curRook);
        ull rookMobility = rookAttackRay(brd->occupancies[both], curRook) & (~brd->occupancies[white]);
        int rookMobilityCount = countBits(rookMobility);

        // Mobility evaluation
        midMobilityEval += mobilityBonus[3][rookMobilityCount][0];
        endMobilityEval += mobilityBonus[3][rookMobilityCount][1];

        // King safety evaluation
        int bKingZoneAttacks = countBits(blackKingZones[brd->blackKingPos] & rookAttackRay(brd->occupancies[both], curRook));
        whiteKingScore += bKingZoneAttacks * attackUnits[R];
    }

    //Queen
    ull wQueenPositions = brd->bitboards[Q];
    while (wQueenPositions) {
        int curQueen = getLSB(wQueenPositions);
        clearBit(wQueenPositions, curQueen);
        ull queenMobility = queenAttackRay(brd->occupancies[both], curQueen) & (~brd->occupancies[white]);
        int queenMobilityCount = countBits(queenMobility);

        // Mobility evaluation
        midMobilityEval += mobilityBonus[4][queenMobilityCount][0];
        endMobilityEval += mobilityBonus[4][queenMobilityCount][1];

        // King safety evaluation
        int bKingZoneAttacks = countBits(blackKingZones[brd->blackKingPos] & queenAttackRay(brd->occupancies[both], curQueen));
        whiteKingScore += bKingZoneAttacks * attackUnits[Q];
    }

    //BLACK

    //Knight
    ull bKnightPositions = brd->bitboards[n];
    while (bKnightPositions) {
        int curKnight = getLSB(bKnightPositions);
        clearBit(bKnightPositions, curKnight);

        //Counts how many non-white squares attacked
        ull knightMobility = knightAttacks[curKnight] & (~brd->occupancies[black]);
        int knightMobilityCount = countBits(knightMobility);

        //Mobility evaluation
        midMobilityEval -= mobilityBonus[1][knightMobilityCount][0];
        endMobilityEval -= mobilityBonus[1][knightMobilityCount][1];

        //King safety evaluation
        int wKingZoneAttacks = countBits(whiteKingZones[brd->whiteKingPos] & knightAttacks[curKnight]);
        blackKingScore += wKingZoneAttacks * attackUnits[n];

    }

    //Bishop
    ull bBishopPositions = brd->bitboards[b];
    while (bBishopPositions) {
        int curBishop = getLSB(bBishopPositions);
        clearBit(bBishopPositions, curBishop);
        ull bishopMobility = bishopAttackRay(brd->occupancies[both],curBishop) & (~brd->occupancies[black]);
        int bishopMobilityCount = countBits(bishopMobility);

        //Mobility evaluation
        midMobilityEval -= mobilityBonus[2][bishopMobilityCount][0];
        endMobilityEval -= mobilityBonus[2][bishopMobilityCount][1];

        //King safety evaluation
        int wKingZoneAttacks = countBits(whiteKingZones[brd->whiteKingPos] & bishopAttackRay(brd->occupancies[both],curBishop));
        blackKingScore += wKingZoneAttacks * attackUnits[b];

    }

    //Rook
    ull bRookPositions = brd->bitboards[r];
    while (bRookPositions) {
        int curRook = getLSB(bRookPositions);
        clearBit(bRookPositions, curRook);
        ull rookMobility = rookAttackRay(brd->occupancies[both], curRook) & (~brd->occupancies[black]);
        int rookMobilityCount = countBits(rookMobility);

        //Mobility evaluation
        midMobilityEval -= mobilityBonus[3][rookMobilityCount][0];
        endMobilityEval -= mobilityBonus[3][rookMobilityCount][1];

        //King safety evaluation
        int wKingZoneAttacks = countBits(whiteKingZones[brd->whiteKingPos] & rookAttackRay(brd->occupancies[both], curRook));
        blackKingScore += wKingZoneAttacks * attackUnits[r];
    }

    //Queen
    ull bQueenPositions = brd->bitboards[q];
    while (bQueenPositions) {
        int curQueen = getLSB(bQueenPositions);
        clearBit(bQueenPositions, curQueen);
        ull queenMobility = queenAttackRay(brd->occupancies[both], curQueen) & (~brd->occupancies[black]);
        int queenMobilityCount = countBits(queenMobility);

        //Mobility evaluation
        midMobilityEval -= mobilityBonus[4][queenMobilityCount][0];
        endMobilityEval -= mobilityBonus[4][queenMobilityCount][1];

        //King safety evaluation
        int wKingZoneAttacks = countBits(whiteKingZones[brd->whiteKingPos] & queenAttackRay(brd->occupancies[both], curQueen));
        blackKingScore += wKingZoneAttacks * attackUnits[q];
    }

    kingSafetyEval = safetyTable[whiteKingScore] - safetyTable[blackKingScore]; //Actual score
}

ull makeWhiteKingZones(int sq){
    ull bb = 0ll;
    int rank = sq/8, file = sq % 8;

    setBit(bb, sq);
    if (rank + 1 < 8){ setBit(bb, sq + 8); }
    if (rank - 1 >= 0){ setBit(bb, sq - 8); }
    if (rank + 1 < 8 && file + 1 < 8){ setBit(bb, sq + 8 + 1); }
    if (rank + 1 < 8 && file - 1 >= 0){ setBit(bb, sq + 8 - 1); }
    if (rank - 1 >= 0 && file + 1 < 8){ setBit(bb, sq - 8 + 1); }
    if (rank - 1 >= 0 && file - 1 >= 0){ setBit(bb, sq - 8 - 1); }
    if (rank + 2 < 8) setBit(bb, sq + 2*8);
    if (rank + 2 < 8 && file + 1 < 8) setBit(bb, sq+ 2*8 + 1);
    if (rank + 2 < 8 && file - 1 >= 0) setBit(bb, sq + 2*8 - 1);

    if (file + 1 < 8){ setBit(bb, sq + 1); }
    if (file - 1 >= 0){ setBit(bb, sq - 1); }


    return bb;
}

ull makeBlackKingZones(int sq){
    ull bb = 0ll;
    int rank = sq/8, file = sq % 8;

    setBit(bb, sq);
    if (rank + 1 < 8){ setBit(bb, sq + 8); }
    if (rank - 1 >= 0){ setBit(bb, sq - 8); }
    if (rank + 1 < 8 && file + 1 < 8){ setBit(bb, sq + 8 + 1); }
    if (rank + 1 < 8 && file - 1 >= 0){ setBit(bb, sq + 8 - 1); }
    if (rank - 1 >= 0 && file + 1 < 8){ setBit(bb, sq - 8 + 1); }
    if (rank - 1 >= 0 && file - 1 >= 0){ setBit(bb, sq - 8 - 1); }
    if (rank - 2 >= 0) setBit(bb, sq - 2*8);
    if (rank - 2 >= 0 && file + 1 < 8) setBit(bb, sq - 2*8 + 1);
    if (rank - 2 >= 0 && file - 1 >= 0) setBit(bb, sq - 2*8 - 1);

    if (file + 1 < 8) setBit(bb, sq + 1);
    if (file - 1 >= 0){ setBit(bb, sq - 1); }


    return bb;
}


void initKingZones() {
    for (int i = 0; i < 64; i++) {
        whiteKingZones[i] = makeWhiteKingZones(i);
        blackKingZones[i] = makeBlackKingZones(i);
    }
}
