
#include "nonSlidersAttacks.h"

ull pawnAttackMask(int sq){
    ull bb = 0ll;
    int rank = sq/8, file = sq % 8;

    // Can attack Up Right if file is larger than a-file and rank
    // is less than the 8th-rank
    if (file > 0 && rank < 8){ setBit(bb, sq + 7); }
    // Up Left
    if (file < 7 && rank < 7){ setBit(bb, sq + 9); }

    return bb;
}

ull knightAttackMask(int sq){
    ull bb = 0ull;
    int rank = sq/8, file = sq % 8;

    if (rank + 2 < 8 && file + 1 < 8){ setBit(bb, sq + 2*8 + 1); }
    if (rank + 2 < 8 && file - 1 >= 0){ setBit(bb, sq + 2*8 - 1); }
    if (rank - 2 >= 0 && file + 1 < 8){ setBit(bb, sq - 2*8 + 1); }
    if (rank - 2 >= 0 && file - 1 >= 0){ setBit(bb, sq - 2*8 - 1); }
    if (rank + 1 < 8 && file + 2 < 8){ setBit(bb, sq + 8 + 2); }
    if (rank + 1 < 8 && file - 2 >= 0){ setBit(bb, sq + 8 - 2); }
    if (rank - 1 >= 0 && file - 2 >= 0){ setBit(bb, sq - 8 - 2); }
    if (rank - 1 >= 0 && file + 2 < 8){ setBit(bb, sq - 8 + 2); }

    return bb;
}

ull kingAttackMask(int sq){
    ull bb = 0ll;
    int rank = sq/8, file = sq % 8;

    if (rank + 1 < 8){ setBit(bb, sq + 8); }
    if (rank - 1 >= 0){ setBit(bb, sq - 8); }
    if (file + 1 < 8){ setBit(bb, sq + 1); }
    if (file - 1 >= 0){ setBit(bb, sq - 1); }
    if (rank + 1 < 8 && file + 1 < 8){ setBit(bb, sq + 8 + 1); }
    if (rank + 1 < 8 && file - 1 >= 0){ setBit(bb, sq + 8 - 1); }
    if (rank - 1 >= 0 && file + 1 < 8){ setBit(bb, sq - 8 + 1); }
    if (rank - 1 >= 0 && file - 1 >= 0){ setBit(bb, sq - 8 - 1); }

    return bb;
}


/// ----------- INITS ------------ ///
/// Must be initialized at startup ///
/// Fills arrays with attack bb's  ///

// Array: pawnAttacks
void initPawnAttacks(){
    for (int sq = 0; sq < 64; sq++){
        pawnAttacks[sq] = pawnAttackMask(sq);
    }
}

// Array: knightAttacks
void initKnightAttacks(){
    for (int sq = 0; sq < 64; sq++){
        knightAttacks[sq] = knightAttackMask(sq);
    }
}

// Array: kingAttacks
void initKingAttacks(){
    for (int sq = 0; sq < 64; sq++){
        kingAttacks[sq] = kingAttackMask(sq);
    }
}

