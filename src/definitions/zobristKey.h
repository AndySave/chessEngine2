
#ifndef CHESSENGINE2_ZOBRISTKEY_H
#define CHESSENGINE2_ZOBRISTKEY_H

#include "board.h"
#include "../utils/bitops.h"
#include "std_typedef.h"
#include <random>

#define hashPiece(key, pce, sq) brd->hashKey ^= pieceKeys[pce][sq];
#define hashSide(key) brd->hashKey ^= sideKey;
#define hashCastle(key, castle) brd->hashKey ^= castleKeys[castle]
#define hashEnpassant(key, enpassantSq) brd->hashKey ^= enpassantKeys[enpassantSq];

extern ull pieceKeys[12][64];
extern ull sideKey;
extern ull castleKeys[16];
extern ull enpassantKeys[64];

ull rand64();

void initHashkeys();

ull generateHash(Board *brd);

#endif
