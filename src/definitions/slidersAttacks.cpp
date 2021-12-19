
#include "slidersAttacks.h"

ull incrementalBishopAttack(int sq){
    ull bb = 0ull;
    int rank = sq/8, file = sq % 8;

    int xDir = 1, yDir = 1;
    while (file + xDir < 7 && rank + yDir < 7){
        setBit(bb, sq + yDir*8 + xDir);
        xDir++;
        yDir++;
    }

    xDir = 1, yDir = -1;
    while (file + xDir < 7 && rank + yDir > 0){
        setBit(bb, sq + yDir*8 + xDir);
        xDir++;
        yDir--;
    }

    xDir = -1, yDir = 1;
    while (file + xDir > 0 && rank + yDir < 7){
        setBit(bb, sq + yDir*8 + xDir);
        xDir--;
        yDir++;
    }

    xDir = -1, yDir = -1;
    while (file + xDir > 0 && rank + yDir > 0){
        setBit(bb, sq + yDir*8 + xDir);
        xDir--;
        yDir--;
    }

    return bb;
}


ull incrementalRookAttack(int sq){
    ull bb = 0ull;
    int rank = sq/8, file = sq % 8;

    int dir = 1;
    while (file + dir < 7){
        setBit(bb, sq + dir);
        dir++;
    }

    dir = -1;
    while (file + dir > 0){
        setBit(bb, sq + dir);
        dir--;
    }

    dir = 1;
    while (rank + dir < 7){
        setBit(bb, sq + dir*8);
        dir++;
    }

    dir = -1;
    while (rank + dir > 0){
        setBit(bb, sq + dir*8);
        dir--;
    }

    return bb;
}


/// ----------- INITS ------------ ///
/// Must be initialized at startup ///
/// Fills arrays with attack bb's  ///

// Array: bishopAttackMasks
void initBishopAttackMasks(){
    for (int sq = 0; sq < 64; sq++){
        bishopAttackMasks[sq] = incrementalBishopAttack(sq);
    }
}

// Array: rookAttackMasks
void initRookAttackMasks(){
    for (int sq = 0; sq < 64; sq++){
        rookAttackMasks[sq] = incrementalRookAttack(sq);
    }
}




