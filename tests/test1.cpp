#include "../src/definitions/move.h"

#include <gtest/gtest.h>

struct MagicTest : public ::testing::Test {
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }
};
/*
 * A move consists of 16 bits:
 * Bits [1, 2] : Special move flag. 00 = nothing, 01 = promotion, 10 = en passant, 11 = castling
 * Bits [3, 4] : Promoted piece. 00 = knight, 01 = bishop, 10 = rook, 11 = queen
 * Bits [5, 10]: To square. Square piece is being moved to. Value from 0-63 inclusive.
 * Bits [11,16]: From square. Square piece is being moved from. Value from 0-63 inclusive.
 */
TEST(MagicTest, createMove) {
    //unsigned short createMove(int fromSq, int toSq, int promotedPiece, int moveFlag)
    ASSERT_EQ(createMove(54, 50, 1, 3), 56502);

}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}





