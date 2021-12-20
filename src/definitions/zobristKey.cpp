
#include "zobristKey.h"

ull rand64(){
    ull n = (ull)rand() + ((ull)rand() << 15) + ((ull)rand() << 30) + ((ull)rand() << 45) + (((ull)rand() & 0xf) << 60);
    return n;
}

ull pieceKeys[12][64];
ull sideKey;
ull castleKeys[16];
ull enpassantKeys[64];


void initHashkeys(){
    for (int pce = 0; pce < 12; pce++){
        for (int sq = 0; sq < 64; sq++){
            pieceKeys[pce][sq] = rand64();
        }
    }

    sideKey = rand64();

    for (int i = 0; i < 16; i++){
        castleKeys[i] = rand64();
    }

    for (int i = 0; i < 64; i++){
        enpassantKeys[i] = rand64();
    }
}


ull generateHash(Board *brd){
    ull key = 0;

    for (int pce = 0; pce < 12; pce++){
        ull bb = brd->bitboards[pce];

        while (bb){
            ull index = getLSB(bb);
            clearBit(bb, index);
            key ^= pieceKeys[pce][index];
        }
    }

    if (brd->side == white){
        key ^= sideKey;
    }

    if (brd->enpassantSq != noSq){
        key ^= enpassantKeys[brd->enpassantSq];
    }

    key ^= castleKeys[brd->castle];

    return key;
}

