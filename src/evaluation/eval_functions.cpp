#include "eval_functions.h"

void initMobility(Board* brd) {
    numOfPieces = 0;
    //WHITE

    //Knight
    ull wKnightPositions = brd->bitboards[N];
    while (wKnightPositions) {
        int curKnight = getLSB(wKnightPositions);
        clearBit(wKnightPositions, curKnight);

        //Counts how many non-white squares attacked
        ull knightMobility = knightAttacks[curKnight] & (~brd->occupancies[white]);

        presentPieces[numOfPieces] = curKnight;
        numOfPieces++;
        pieceOfSquare[curKnight] = N;

        mobilityMasks[curKnight] = knightMobility;
        mobility[curKnight] = countBits(knightMobility);

    }

    //Bishop
    ull wBishopPositions = brd->bitboards[B];
    while (wBishopPositions) {
        int curBishop = getLSB(wBishopPositions);
        clearBit(wBishopPositions, curBishop);
        ull bishopMobility = bishopAttackRay(brd->occupancies[both], curBishop) & (~brd->occupancies[white]);

        presentPieces[numOfPieces] = curBishop;
        numOfPieces++;
        pieceOfSquare[curBishop] = B;

        mobilityMasks[curBishop] = bishopMobility;
        mobility[curBishop] = countBits(bishopMobility);
    }

    //Rook
    ull wRookPositions = brd->bitboards[R];
    while (wRookPositions) {
        int curRook = getLSB(wRookPositions);
        clearBit(wRookPositions, curRook);
        ull rookMobility = rookAttackRay(brd->occupancies[both], curRook) & (~brd->occupancies[white]);

        presentPieces[numOfPieces] = curRook;
        numOfPieces++;
        pieceOfSquare[curRook] = R;

        mobilityMasks[curRook] = rookMobility;
        mobility[curRook] = countBits(rookMobility);
    }

    //Queen
    ull wQueenPositions = brd->bitboards[Q];
    while (wQueenPositions) {
        int curQueen = getLSB(wQueenPositions);
        clearBit(wQueenPositions, curQueen);
        ull queenMobility = queenAttackRay(brd->occupancies[both], curQueen) & (~brd->occupancies[white]);

        presentPieces[numOfPieces] = curQueen;
        numOfPieces++;
        pieceOfSquare[curQueen] = Q;

        mobilityMasks[curQueen] = queenMobility;
        mobility[curQueen] = countBits(queenMobility);
    }

    //BLACK

    //Knight
    ull bKnightPositions = brd->bitboards[n];
    while (bKnightPositions) {
        int curKnight = getLSB(bKnightPositions);
        clearBit(bKnightPositions, curKnight);

        //Counts how many non-white squares attacked
        ull knightMobility = knightAttacks[curKnight] & (~brd->occupancies[black]);

        presentPieces[numOfPieces] = curKnight;
        numOfPieces++;
        pieceOfSquare[curKnight] = n;

        mobilityMasks[curKnight] = knightMobility;
        mobility[curKnight] = countBits(knightMobility);
    }

    //Bishop
    ull bBishopPositions = brd->bitboards[b];
    while (bBishopPositions) {
        int curBishop = getLSB(bBishopPositions);
        clearBit(bBishopPositions, curBishop);
        ull bishopMobility = bishopAttackRay(brd->occupancies[both],curBishop) & (~brd->occupancies[black]);

        presentPieces[numOfPieces] = curBishop;
        numOfPieces++;
        pieceOfSquare[curBishop] = b;

        mobilityMasks[curBishop] = bishopMobility;
        mobility[curBishop] = countBits(bishopMobility);

    }

    //Rook
    ull bRookPositions = brd->bitboards[r];
    while (bRookPositions) {
        int curRook = getLSB(bRookPositions);
        clearBit(bRookPositions, curRook);
        ull rookMobility = rookAttackRay(brd->occupancies[both], curRook) & (~brd->occupancies[black]);

        presentPieces[numOfPieces] = curRook;
        numOfPieces++;
        pieceOfSquare[curRook] = r;

        mobilityMasks[curRook] = rookMobility;
        mobility[curRook] = countBits(rookMobility);
    }

    //Queen
    ull bQueenPositions = brd->bitboards[q];
    while (bQueenPositions) {
        int curQueen = getLSB(bQueenPositions);
        clearBit(bQueenPositions, curQueen);
        ull queenMobility = queenAttackRay(brd->occupancies[both], curQueen) & (~brd->occupancies[black]);

        presentPieces[numOfPieces] = curQueen;
        numOfPieces++;
        pieceOfSquare[curQueen] = q;

        mobilityMasks[curQueen] = queenMobility;
        mobility[curQueen] = countBits(queenMobility);
    }
}
