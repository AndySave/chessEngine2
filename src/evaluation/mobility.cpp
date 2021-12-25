#include "mobility.h"

void mobilityEvaluation(Board *brd) {
    //husk ikke bevege oppaa egene brikker
    midMobility = 0;
    endMobility = 0;

    //WHITE

    //Knight
    ull wKnightPositions = brd->bitboards[N];
    while (wKnightPositions) {
        int curKnight = getLSB(wKnightPositions);
        clearBit(wKnightPositions, curKnight);

        //Counts how many non-white squares attacked
        int knightMobility = countBits(knightAttacks[curKnight] & (~brd->occupancies[white]));

        midMobility += mobilityBonus[1][knightMobility][0];
        endMobility += mobilityBonus[1][knightMobility][1];
    }

    //Bishop
    ull wBishopPositions = brd->bitboards[B];
    while (wBishopPositions) {
        int curBishop = getLSB(wBishopPositions);
        clearBit(wBishopPositions, curBishop);
        int bishopMobility = countBits(bishopAttackRay(brd->bitboards[both],curBishop) & (~brd->bitboards[white]));
        midMobility += mobilityBonus[2][bishopMobility][0];
        endMobility += mobilityBonus[2][bishopMobility][1];

    }

    //Rook
    ull wRookPositions = brd->bitboards[R];
    while (wRookPositions) {
        int curRook = getLSB(wRookPositions);
        clearBit(wRookPositions, curRook);
        int rookMobility = countBits(rookAttackRay(brd->bitboards[both], curRook) & (~brd->bitboards[white]));
        midMobility += mobilityBonus[3][rookMobility][0];
        endMobility += mobilityBonus[3][rookMobility][1];
    }

    //Queen
    ull wQueenPositions = brd->bitboards[Q];
    while (wQueenPositions) {
        int curQueen = getLSB(wQueenPositions);
        clearBit(wQueenPositions, curQueen);
        int queenMobility = countBits(queenAttackRay(brd->bitboards[both], curQueen) & (~brd->bitboards[white]));
        midMobility += mobilityBonus[4][queenMobility][0];
        endMobility += mobilityBonus[4][queenMobility][1];
    }

    //BLACK

    //Knight
    ull bKnightPositions = brd->bitboards[n];
    while (bKnightPositions) {
        int curKnight = getLSB(bKnightPositions);
        clearBit(bKnightPositions, curKnight);

        //Counts how many non-white squares attacked
        int knightMobility = countBits(knightAttacks[curKnight] & (~brd->occupancies[black]));

        midMobility -= mobilityBonus[1][knightMobility][0];
        endMobility -= mobilityBonus[1][knightMobility][1];
    }

    //Bishop
    ull bBishopPositions = brd->bitboards[b];
    while (bBishopPositions) {
        int curBishop = getLSB(bBishopPositions);
        clearBit(bBishopPositions, curBishop);
        int bishopMobility = countBits(bishopAttackRay(brd->bitboards[both],curBishop) & (~brd->bitboards[black]));
        midMobility -= mobilityBonus[2][bishopMobility][0];
        endMobility -= mobilityBonus[2][bishopMobility][1];

    }

    //Rook
    ull bRookPositions = brd->bitboards[r];
    while (bRookPositions) {
        int curRook = getLSB(bRookPositions);
        clearBit(bRookPositions, curRook);
        int rookMobility = countBits(rookAttackRay(brd->bitboards[both], curRook) & (~brd->bitboards[black]));
        midMobility -= mobilityBonus[3][rookMobility][0];
        endMobility -= mobilityBonus[3][rookMobility][1];
    }

    //Queen
    ull bQueenPositions = brd->bitboards[q];
    while (bQueenPositions) {
        int curQueen = getLSB(bQueenPositions);
        clearBit(bQueenPositions, curQueen);
        int queenMobility = countBits(queenAttackRay(brd->bitboards[both], curQueen) & (~brd->bitboards[black]));
        midMobility -= mobilityBonus[4][queenMobility][0];
        endMobility -= mobilityBonus[4][queenMobility][1];
    }
}

