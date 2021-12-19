#include <iostream>
#include "../utils/bitops.h"
#include "../definitions/enums.h"
#include "../definitions/nonSlidersAttacks.h"
#include "../definitions/slidersAttacks.h"


// TODO: Make unit test
bool bishopMagicsTest(){
    cout << "Starting bishop magics test" << endl;
    for (int sq = 0; sq < 64; sq++){
        ull mag = bishopMagics[sq];
        ull bb = bishopAttackMasks[sq];

        int bitsInAttackMask = countBits(bb);

        int indices[1 << bitsInAttackMask];
        for (int i = 0; i < (1 << bitsInAttackMask); i++){
            indices[i] = 0;
        }

        for (int i = 0; i < (1ll << bitsInAttackMask); i++){
            ull occ = generateOccupancy(bb, i);
            occ *= mag;
            occ >>= (64-bitsInAttackMask);

            if (indices[occ]){
                cout << "Magic number#" << sq << ": " << mag << " failed!" << endl;
                cout << "Index " << indices[occ]-1 << " collided with index " << i << endl;
                return false;
            }

            indices[occ] = i+1;
        }
    }

    cout << "All magic numbers work" << endl;
    return true;
}

// TODO: Make unit test
bool rookMagicsTest(){
    cout << "Starting rook magics test" << endl;
    for (int sq = 0; sq < 64; sq++){
        ull mag = rookMagics[sq];
        ull bb = rookAttackMasks[sq];

        int bitsInAttackMask = countBits(bb);

        int indices[1 << bitsInAttackMask];
        for (int i = 0; i < (1 << bitsInAttackMask); i++){
            indices[i] = 0;
        }

        for (int i = 0; i < (1ll << bitsInAttackMask); i++){
            ull occ = generateOccupancy(bb, i);
            occ *= mag;
            occ >>= (64-bitsInAttackMask);

            if (indices[occ]){
                cout << "Magic number#" << sq << ": " << mag << " failed!" << endl;
                cout << "Index " << indices[occ]-1 << " collided with index " << i << endl;
                return false;
            }

            indices[occ] = sq;
        }
    }

    cout << "All magic numbers work" << endl;
    return true;
}


int main() {

    initBitMasks();
    initPawnAttacks();
    initKnightAttacks();
    initKingAttacks();
    initBishopAttackMasks();
    initRookAttackMasks();

    bishopMagicsTest();
    rookMagicsTest();
}


