
#include "slidersAttacks.h"

ull generateOccupancy(ull attackMask, int index){
    ull occupancy = 0ULL;
    int bitsInAttackMask = countBits(attackMask);

    for (int count = 0; count < bitsInAttackMask; count++){
        int square = getLSB(attackMask);
        clearBit(attackMask, square);

        if (index & (1 << count)){
            occupancy |= (1ULL << square);
        }
    }

    return occupancy;
}


ull generateBishopAttackMask(int sq){
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


ull generateRookAttackMask(int sq){
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

ull incrementalBishopAttack(ull occ, int sq){
    ull bb = 0ull;
    int rank = sq/8, file = sq % 8;

    int xDir = 1, yDir = 1;
    while (file + xDir < 8 && rank + yDir < 8){
        setBit(bb, sq + yDir*8 + xDir);
        if (getBit(occ, sq + yDir*8 + xDir)){
            break;
        }

        xDir++;
        yDir++;
    }

    xDir = 1, yDir = -1;
    while (file + xDir < 8 && rank + yDir >= 0){
        setBit(bb, sq + yDir*8 + xDir);
        if (getBit(occ, sq + yDir*8 + xDir)){
            break;
        }

        xDir++;
        yDir--;
    }

    xDir = -1, yDir = 1;
    while (file + xDir >= 0 && rank + yDir < 8){
        setBit(bb, sq + yDir*8 + xDir);
        if (getBit(occ, sq + yDir*8 + xDir)){
            break;
        }

        xDir--;
        yDir++;
    }

    xDir = -1, yDir = -1;
    while (file + xDir >= 0 && rank + yDir >= 0){
        setBit(bb, sq + yDir*8 + xDir);
        if (getBit(occ, sq + yDir*8 + xDir)){
            break;
        }

        xDir--;
        yDir--;
    }

    return bb;
}


ull incrementalRookAttack(ull occ, int sq){
    ull bb = 0ull;
    int rank = sq/8, file = sq % 8;

    int dir = 1;
    while (file + dir < 8){
        setBit(bb, sq + dir);
        if (getBit(occ, sq+dir)){
            break;
        }

        dir++;
    }

    dir = -1;
    while (file + dir >= 0){
        setBit(bb, sq + dir);
        if (getBit(occ, sq+dir)){
            break;
        }

        dir--;
    }

    dir = 1;
    while (rank + dir < 8){
        setBit(bb, sq + dir*8);
        if (getBit(occ, sq+dir*8)){
            break;
        }

        dir++;
    }

    dir = -1;
    while (rank + dir >= 0){
        setBit(bb, sq + dir*8);
        if (getBit(occ, sq+dir*8)){
            break;
        }

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
        bishopAttackMasks[sq] = generateBishopAttackMask(sq);
    }
}

// Array: rookAttackMasks
void initRookAttackMasks(){
    for (int sq = 0; sq < 64; sq++){
        rookAttackMasks[sq] = generateRookAttackMask(sq);
    }
}




