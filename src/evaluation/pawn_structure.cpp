
#include "pawn_structure.h"

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
