#include "bitops.h"

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