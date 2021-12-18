#ifndef CHESSENGINE2_BITOPS_H
#define CHESSENGINE2_BITOPS_H

#include "../definitions/std_typedef.h"

inline ull setMask[64];
inline ull clearMask[64];

void initBitMasks();

inline void clearBit(ull &bitBoard, int sq){
    bitBoard &= clearMask[sq];
}

inline void setBit(ull &bitBoard, int sq){
    bitBoard |= setMask[sq];
}

inline int countBits(ull bitBoard){
    int count = 0;

    while (bitBoard){
        count++;
        bitBoard &= bitBoard - 1;
    }
    return count;
}

#endif
