#include <gtest/gtest.h>
#include <fstream>
#include "../../src/utils/bitops.h"
#include "../../src/definitions/nonSlidersAttacks.h"
#include "../../src/definitions/slidersAttacks.h"
#include "../../src/definitions/zobristKey.h"
#include "../../src/utils/fen.h"
#include "../../src/definitions/board.h"
#include "../../src/definitions/moveGeneration.h"
#include "../../src/evaluation/mainEvaluation.h"

struct PerftTest : public ::testing::Test {
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }
};

int cnt = 0;

void setup() {
    initBitMasks();
    initWhitePawnAttacks();
    initBlackPawnAttacks();
    initKnightAttacks();
    initKingAttacks();
    initBishopAttackMasks();
    initRookAttackMasks();
    initHashkeys();

    fillBishopAttacksArray();
    fillRookAttacksArray();
}

//Splits a string using a delimiter
vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

void perftRec(Board* brd, int depth) {
    if (depth <= 0) { // Base case
        cnt++;
        return;
    }

    Movelist moveList;
    generateMoves(brd, &moveList);

    for (int i = 0 ; i<moveList.count; i++) {
        bool legalMove = makeMove(brd, moveList.moves[i].move);
        if (legalMove) {
            perftRec(brd, depth-1);
            undoMove(brd);
        }
    }
}

TEST(PerftTest, perft) {
    setup();

    //read from file
    vector<string> lines;
    ifstream file("../tests/definitions/perft_testcases.txt");
    if (file.is_open()) {
        string line;
        while (std::getline(file, line)) lines.push_back(line);
        file.close();
    }

    int n = lines.size(); // file entries
    ll solutions[n][7]; //solutions, solutions[which test][depth (range 1->6)]
    string fenPositions[n]; // positions fen

    for (int i = 0; i<n; i++) {
        vector<string> elms = split(lines[i], " ;");
        fenPositions[i] = elms[0];
        for (int j = 1; j<=6; j++) {
            string sol = "";
            for (int k = 3; k<elms[j].size(); k++) {
                sol += elms[j][k];
            }
            solutions[i][j] = stoll(sol);
        }
    }

    //perft test
    for (int i = 0; i<n; i++) {
        Board brd;
        FEN(&brd, fenPositions[i]);
        if (i == 1) continue;


        for (int j = 1; j<=6; j++) {
            perftRec(&brd, j);
            FEN(&brd, fenPositions[i]);

            EXPECT_EQ(cnt, solutions[i][j]);
            cout << cnt << " " << solutions[i][j] << endl;
            cnt = 0;
        }
    }

}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
