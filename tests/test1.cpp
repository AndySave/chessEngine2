#include "../src/definitions/slidersAttacks.h"
#include <gtest/gtest.h>

/*
cout << "Magic number#" << sq << ": " << magic << " failed!" << endl;
cout << "Index " << indices[occ]-1 << " collided with index " << i << endl;
*/

/*
bool magicOk(ull bb, ull magic, int sq){
    sq++;
    int bitsInAttackMask = countBits(bb);

    int indices[1 << bitsInAttackMask];
    for (int i = 0; i < (1 << bitsInAttackMask); i++){
        indices[i] = 0;
    }

    for (int i = 0; i < (1 << bitsInAttackMask); i++){
        ull occ = generateOccupancy(bb, i);
        occ *= magic;
        occ >>= (64-bitsInAttackMask);

        if (indices[occ]){
            return false;
        }

        indices[occ] = sq;
    }

    return true;
}


TEST(bishopMagicsTest, TEST) {

    bool ans = true;

    for (int sq = 0; sq < 64; sq++){
        ull magic = bishopMagics[sq];
        ull bb = bishopAttackMasks[sq];

        ans &= magicOk(bb, magic, sq);
    }

    EXPECT_TRUE(ans);
}


TEST(rookMagicsTest, TEST) {

    bool ans = true;

    for (int sq = 0; sq < 64; sq++){
        ull magic = rookMagics[sq];
        ull bb = rookAttackMasks[sq];

        ans &= magicOk(bb, magic, sq);
    }

    EXPECT_TRUE(ans);
}

*/






