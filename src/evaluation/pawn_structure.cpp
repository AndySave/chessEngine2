
#include "pawn_structure.h"

/*
 * Initializes passed pawn masks for white. Masks are used to determine if a
 * pawn is passed. Must be initialized at start of program after bitMasks.
 */
void initWhitePassedPawnMask(){
    for (int sq = 0; sq < 64; sq++){
        ull bb = 0ull;

        int i = sq;
        i += 8;
        while (i < 64){
            // There will always be a square above a pawn
            setBit(bb, i);
            // Check if square to the left of pawn exists
            if (i % 8 != 0){
                setBit(bb, i-1);
            }
            // Check if square to the right of pawn exists
            if (i % 8 != 7){
                setBit(bb, i+1);
            }

            i += 8;
        }

        whitePassedPawnMasks[sq] = bb;
    }
}

/*
 * Same as initWhitePassedPawnMask except for black pawns
 */
void initBlackPassedPawnMask(){
    for (int sq = 0; sq < 64; sq++){
        ull bb = 0ull;

        int i = sq;
        i -= 8;
        while (i >= 0){
            // There will always be a square above a pawn
            setBit(bb, i);
            // Check if square to the left of pawn exists
            if (i % 8 != 0){
                setBit(bb, i-1);
            }
            // Check if square to the right of pawn exists
            if (i % 8 != 7){
                setBit(bb, i+1);
            }

            i -= 8;
        }

        blackPassedPawnMasks[sq] = bb;
    }
}


/*
 * Returns true if a pawn is passed. Requires color of the pawn you want to check
 */
bool pawnIsPassed(Board *brd, int sq, int color){
    if (color == white){
        if (!(whitePassedPawnMasks[sq] & brd->bitboards[p])){
            return true;
        }
    }else{
        if (!(blackPassedPawnMasks[sq] & brd->bitboards[P])){
            return true;
        }
    }

    return false;
}

/*
 * Loops through all pawns on board and gives them a bonus if they are passed
 * Returns an int score
 * Used in main eval
 */
int passedPawnEvaluation(Board *brd){
    int score = 0;

    ull whitePawns = brd->bitboards[P];
    while (whitePawns){
        int index = getLSB(whitePawns);
        clearBit(whitePawns, index);

        if (pawnIsPassed(brd, index, white)){
            score += passedPawnBonus;
        }
    }

    ull blackPawns = brd->bitboards[p];
    while (blackPawns){
        int index = getLSB(blackPawns);
        clearBit(blackPawns, index);

        if (pawnIsPassed(brd, index, black)){
            score -= passedPawnBonus;
        }
    }

    return score;
}


/*
 * Initializes masks used for detecting isolated pawns
 * Must be called at start of program
 */
void initIsolatedPawnMasks(){
    for (int sq = 0; sq < 64; sq++){
        ull bb = 0ull;

        int file = sq % 8;

        // Edge case for pawn on a file
        if (file - 1 >= 0){
            bb |= files[file-1];
        }
        // Edge case for pawn on h file
        if (file + 1 < 8){
            bb |= files[file+1];
        }

        isolatedPawnMasks[sq] = bb;
    }
}

/*
 * Returns true if a pawn is isolated. Requires color of the pawn you want to check
 */
bool pawnIsIsolated(Board *brd, int sq, int color){
    if (color == white){
        if (!(isolatedPawnMasks[sq] & brd->bitboards[P])){
            return true;
        }
    }else{
        if (!(isolatedPawnMasks[sq] & brd->bitboards[p])){
            return true;
        }
    }

    return false;
}


/*
 * Loops through all pawns on board and gives them a penalty if they are isolated
 * Returns an int score
 * Used in main eval
 */
int isolatedPawnEvaluation(Board *brd){
    int score = 0;

    ull whitePawns = brd->bitboards[P];
    while (whitePawns){
        int index = getLSB(whitePawns);
        clearBit(whitePawns, index);

        if (pawnIsIsolated(brd, index, white)){
            score -= isolatedPawnPenalty;
        }
    }

    ull blackPawns = brd->bitboards[p];
    while (blackPawns){
        int index = getLSB(blackPawns);
        clearBit(blackPawns, index);

        if (pawnIsIsolated(brd, index, black)){
            score += isolatedPawnPenalty;
        }
    }

    return score;
}

/*
 * Initializes backwards pawn masks. Masks are used to determine if a
 * pawn is backwards. Must be initialized at start of program after bitMasks.
 */
void initBackwardPawnMasks(){
    for (int sq = 0; sq < 64; sq++){
        ull bb = 0ull;

        int file = sq % 8;
        // Edge case for pawns on a-file
        if (file - 1 >= 0){
            int tempSq = sq-1;
            while (tempSq >= 0){
                setBit(bb, tempSq);
                tempSq -= 8;
            }
        }
        // Edge case for pawns on h-file
        if (file + 1 < 8){
            int tempSq = sq+1;
            while (tempSq >= 0){
                setBit(bb, tempSq);
                tempSq -= 8;
            }
        }

        backwardsPawnMasks[sq] = bb;
    }
}

/*
 * Returns true if a pawn is backwards. Requires color of the pawn you want to check
 */
bool pawnIsBackwards(Board *brd, int sq, int color){
    if (color == white){
        if (!(files[sq%8] & brd->occupancies[black]) && (whitePawnAttacks[sq+8] & brd->bitboards[p]) && !(backwardsPawnMasks[sq] & brd->bitboards[P])){
            return true;
        }
    }else{
        if (!(files[sq%8] & brd->occupancies[white]) && (blackPawnAttacks[sq-8] & brd->bitboards[P]) && !(backwardsPawnMasks[sq] & brd->bitboards[p])){
            return true;
        }
    }

    return false;
}

/*
 * Loops through all pawns on board and gives them a penalty if they are backwards
 * Returns an int score
 * Used in main eval
 */
int backwardsPawnEvaluation(Board *brd){
    int score = 0;

    ull whitePawns = brd->bitboards[P];
    while (whitePawns){
        int index = getLSB(whitePawns);
        clearBit(whitePawns, index);

        if (pawnIsBackwards(brd, index, white)){
            score -= backwardsPawnPenalty;
        }
    }

    ull blackPawns = brd->bitboards[p];
    while (blackPawns){
        int index = getLSB(blackPawns);
        clearBit(blackPawns, index);

        if (pawnIsBackwards(brd, index, black)){
            score += backwardsPawnPenalty;
        }
    }

    return score;
}

