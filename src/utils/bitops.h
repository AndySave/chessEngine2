
#ifndef CHESSENGINE2_BITOPS_H
#define CHESSENGINE2_BITOPS_H

#include "../definitions/std_typedef.h"
#include <intrin.h>

extern ull setMask[64];
extern ull clearMask[64];

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

constexpr ull m1  = 0x5555555555555555; //binary: 0101...
constexpr ull m2  = 0x3333333333333333; //binary: 00110011..
constexpr ull m4  = 0x0f0f0f0f0f0f0f0f; //binary:  4 zeros,  4 ones ...
constexpr ull h01 = 0x0101010101010101; //the sum of 256 to the power of 0,1,2,3...
inline int countBits(ull x){
    x -= (x >> 1) & m1;
    x = (x & m2) + ((x >> 2) & m2);
    x = (x + (x >> 4)) & m4;
    return (x * h01) >> 56;
}

/*
// Gets index of Least Significant Bit
inline int getLSB(ull bb){
    if (bb != 0)
        return countBits((bb & -bb) - 1);
    return -1;
}
*/


static inline int getLSB(ull &bb) {
    unsigned long index;
    if (_BitScanForward64(&index, bb)){
        return index;
    }
    else{
        return 64;
    }
}



const int DEBRUIJN64[64] = {
        0, 47,  1, 56, 48, 27,  2, 60,
        57, 49, 41, 37, 28, 16,  3, 61,
        54, 58, 35, 52, 50, 42, 21, 44,
        38, 32, 29, 23, 17, 11,  4, 62,
        46, 55, 26, 59, 40, 36, 15, 53,
        34, 51, 20, 43, 31, 22, 10, 45,
        25, 39, 14, 33, 19, 30,  9, 24,
        13, 18,  8, 12,  7,  6,  5, 63
};

const ull MAGIC = 0x03f79d71b4cb0a89;

// Returns the index of the least significant bit in the bitboard
inline ull bsf(ull b) {
    return DEBRUIJN64[MAGIC * (b ^ (b - 1)) >> 58];
}

// Returns the index of the least significant bit in the bitboard, and removes the bit from the bitboard
inline ull popLsb(ull* b) {
    int lsb = bsf(*b);
    *b &= *b - 1;
    return ull(lsb);
}



#endif
