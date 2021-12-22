#include "bitops.h"
#include <iostream>

ull setMask[64];
ull clearMask[64];
void initBitMasks(){
    for (ull &i : setMask){
        i = 0ULL;
    }

    for (int i = 0; i < 64; i++){
        ull b = 1ULL << i;
        setMask[i] |= b;
        clearMask[i] = ~setMask[i];
    }
}

void printBitboard(ull bb){
    for (int rank = 7; rank >= 0; rank--){
        cout << rank+1 << "  ";
        for (int file = 0; file < 8; file++){
            if (bb & (1ull << (rank*8 + file))){
                cout << 1 << " ";
            }else{
                cout << 0 << " ";
            }
        }
        cout << endl;
    }

    cout << endl << "   ";
    for (int i = 0; i < 8; i++){
        cout << char(97+i) << " ";
    }

    cout << endl << "bitboard: " << bb << endl << endl;
}


