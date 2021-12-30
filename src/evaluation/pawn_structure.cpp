
#include "pawn_structure.h"

void initPassedPawnMask(){
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

        passedPawnMasks[sq] = bb;
    }
}




