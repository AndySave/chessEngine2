#include "bitops.h"
#include <iostream>


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
    for (int i = 7; i >= 0; i--){
        cout << i+1 << "  ";
        for (int j = 0; j < 8; j++){
            if (bb & (1ull << (i*8 + j))){
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


