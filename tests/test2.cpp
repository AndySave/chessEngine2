#include <gtest/gtest.h>
#include "../src/definitions/std_typedef.h"
#include "../src/utils/bitops.h"
#include "../src/definitions/slidersAttacks.h"

struct MagicTest : public ::testing::Test {
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
        initBitMasks();
        initBishopAttackMasks();
        initRookAttackMasks();
    }
};

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
            cout << "Magic number #" << sq << ": " << magic << " failed!" << endl;
            cout << "Index " << indices[occ]-1 << " collided with index " << i << endl;
            return false;
        }
        indices[occ] = sq;
    }
    return true;
}

/*
 * COMMENT WHAT TEST DOES
 */
TEST(MagicTest, bishopMagicsTest) {
    initBitMasks();
    initBishopAttackMasks();

    bool ans = true;
    for (int sq = 0; sq < 64; sq++){
        ull magic = bishopMagics[sq];
        ull bb = bishopAttackMasks[sq];
        bool res = magicOk(bb, magic, sq);
        res &= magicOk(bb, magic, sq);
        EXPECT_TRUE(ans);
        if (!res) break;
    }
}

/*
 * COMMENT WHAT TEST DOES
 */
TEST(MagicTest, rookMagicsTest) {
    initBitMasks();
    initRookAttackMasks();

    for (int sq = 0; sq < 64; sq++){
        ull magic = rookMagics[sq];
        ull bb = rookAttackMasks[sq];
        bool res = magicOk(bb, magic, sq);
        EXPECT_TRUE(res);
        if (!res) break;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}