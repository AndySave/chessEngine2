
#include "nonSlidersAttacks.h"


ull whitePawnAttacks[64];
ull blackPawnAttacks[64];
ull whitePawnPush[64];
ull blackPawnPush[64];
ull knightAttacks[64];
ull kingAttacks[64];

ull whitePawnAttackMask(int sq){
    ull bb = 0ll;
    int rank = sq/8, file = sq % 8;

    // Can attack Up Right if file is larger than a-file and rank
    // is less than the 8th-rank
    if (file > 0 && rank < 7){ setBit(bb, sq + 7); }
    // Up Left
    if (file < 7 && rank < 7){ setBit(bb, sq + 9); }

    return bb;
}

ull blackPawnAttackMask(int sq){
    ull bb = 0ll;
    int rank = sq/8, file = sq % 8;

    // Can attack Up Right if file is larger than a-file and rank
    // is less than the 8th-rank
    if (file > 0 && rank > 0){ setBit(bb, sq - 9); }
    // Up Left
    if (file < 7 && rank > 0){ setBit(bb, sq - 7); }

    return bb;
}

ull whitePawnPushMask(int sq){
    ull bb = 0ull;
    int rank = sq/8, file = sq % 8;

    if (rankSquares[sq] == 7){
        return bb;
    }

    setBit(bb, sq+8);

    if (rankSquares[sq] == 1){
        setBit(bb, sq+16);
    }

    return bb;
}

ull blackPawnPushMask(int sq){
    ull bb = 0ull;
    int rank = sq/8, file = sq % 8;

    if (rankSquares[sq] == 0){
        return bb;
    }

    setBit(bb, sq-8);

    if (rankSquares[sq] == 6){
        setBit(bb, sq-16);
    }

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
void initWhitePawnAttacks(){
    for (int sq = 0; sq < 64; sq++){
        whitePawnAttacks[sq] = whitePawnAttackMask(sq);
    }
}

// Array: pawnAttacks
void initBlackPawnAttacks(){
    for (int sq = 0; sq < 64; sq++){
        blackPawnAttacks[sq] = blackPawnAttackMask(sq);
    }
}

// Array: whitePawnPush
void initWhitePushAttacks(){
    for (int sq = 0; sq < 64; sq++){
        whitePawnPush[sq] = whitePawnPushMask(sq);
    }
}

// Array: blackPawnPush
void initBlackPushAttacks(){
    for (int sq = 0; sq < 64; sq++){
        blackPawnPush[sq] = blackPawnPushMask(sq);
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

