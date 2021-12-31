#include "../../src/ui/uci.h"

#include <gtest/gtest.h>

struct UCITest : public ::testing::Test {
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }
};

TEST(UCITest, algebraicMoveToIntTest) {
    // Pre inits
    initBitMasks();
    initWhitePawnAttacks();
    initBlackPawnAttacks();
    initKnightAttacks();
    initKingAttacks();
    initBishopAttackMasks();
    initRookAttackMasks();

    initHashkeys();

    initMvvLva();

    fillBishopAttacksArray();
    fillRookAttacksArray();

    Board b1; FEN(&b1, "r5k1/pb2bppp/1p2pn2/2p3B1/2Bq4/3P3Q/PPP2PPP/R3R1K1 w - - 0 17");
    postInit(&b1);
    int m1 = algebraicMoveToInt("c4e6", &b1);
    int cm1 = createMove(c4, e6, 0, noFlag, B, p);

    Board b2; FEN(&b2, "rnbq1rk1/ppppb1pp/4pn2/5p2/2PP4/5NP1/PP2PPBP/RNBQ1RK1 b - - 0 6");
    postInit(&b2);
    int m2 = algebraicMoveToInt("d8e8", &b2);
    int cm2 = createMove(d8, e8, 0, noFlag, q, noPiece);

    Board b3; FEN(&b3, "rnbq1rk1/ppppb1pp/4pn2/5p2/2P5/5NP1/PP1PPPBP/RNBQ1RK1 w - - 4 6");
    postInit(&b3);
    int m3 = algebraicMoveToInt("d2d4", &b3);
    int cm3 = createMove(d2, d4, 0, noFlag, P, noPiece);

    Board b4; FEN(&b4, "rnbq1rk1/2ppb1pp/p3pn2/1pP2p2/3P4/5NP1/PP2PPBP/RNBQ1RK1 w - b6 0 8");
    postInit(&b4);
    int m4 = algebraicMoveToInt("c5b6", &b4);
    int cm4 = createMove(c5, b6, 0, epFlag, P, noPiece);

    EXPECT_EQ(m1, cm1);
    EXPECT_EQ(m2, cm2);
    EXPECT_EQ(m3, cm3);
    EXPECT_EQ(m4, cm4);

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}