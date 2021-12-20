#include <iostream>
#include "../utils/bitops.h"
#include "../definitions/nonSlidersAttacks.h"
#include "../definitions/slidersAttacks.h"
#include "../definitions/zobristKey.h"
#include "../utils/fen.h"
#include "../definitions/board.h"
#include "../utils/board_utils.h"

bool magicOk(ull bb, ull magic, int sq, bool debugMsg){
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
            if (debugMsg){
                cout << "Magic number#" << sq << ": " << magic << " failed!" << endl;
                cout << "Index " << indices[occ]-1 << " collided with index " << i << endl;
            }
            return false;
        }

        indices[occ] = sq;
    }

    return true;
}


// TODO: Make unit test
bool bishopMagicsTest(){
    cout << "Starting bishop magics test" << endl;
    for (int sq = 0; sq < 64; sq++){
        ull magic = bishopMagics[sq];
        ull bb = bishopAttackMasks[sq];

        if (!magicOk(bb, magic, sq, true)){
            return false;
        }
    }

    cout << "All magic numbers work" << endl;
    return true;
}

// TODO: Make unit test
bool rookMagicsTest(){
    cout << "Starting rook magics test" << endl;
    for (int sq = 0; sq < 64; sq++){
        ull magic = rookMagics[sq];
        ull bb = rookAttackMasks[sq];

        if (!magicOk(bb, magic, sq, true)){
            return false;
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
    initHashkeys();

    bishopMagicsTest();
    rookMagicsTest();

    fillBishopAttacksArray();
    fillRookAttacksArray();


    Board board;
    string fenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    FEN(&board, fenString);
    printBoard(&board);
}





