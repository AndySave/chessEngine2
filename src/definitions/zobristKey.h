
#ifndef CHESSENGINE2_ZOBRISTKEY_H
#define CHESSENGINE2_ZOBRISTKEY_H

#include "board.h"
#include "../utils/bitops.h"
#include "std_typedef.h"
#include <random>

#define hashPiece(pce, sq) brd->hashKey ^= pieceKeys[pce][sq];
#define hashSide brd->hashKey ^= sideKey;
#define hashCastle(castle) brd->hashKey ^= castleKeys[castle]
#define hashEnpassant(enpassantSq) brd->hashKey ^= enpassantKeys[enpassantSq];

extern ull pieceKeys[12][64];
extern ull sideKey;
extern ull castleKeys[16];
extern ull enpassantKeys[64];

ull rand64();

void initHashkeys();

ull generateHash(Board *brd);

#endif
