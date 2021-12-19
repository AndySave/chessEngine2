
#ifndef CHESSENGINE2_BITOPS_H
#define CHESSENGINE2_BITOPS_H

#include "../definitions/std_typedef.h"

inline ull setMask[64];
inline ull clearMask[64];

void initBitMasks();
void printBitboard(ull bb);

inline int getBit(ull &bitBoard, int sq){
    return bitBoard & setMask[sq] ? 1 : 0;
}

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

// Gets index of Least Significant Bit
inline int getLSB(ull bb){
    if (bb != 0)
        return countBits((bb & -bb) - 1);
    return -1;
}

#endif
