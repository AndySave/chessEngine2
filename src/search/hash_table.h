
#ifndef CHESSENGINE2_HASH_TABLE_H
#define CHESSENGINE2_HASH_TABLE_H

#include "../definitions/std_typedef.h"
#include "../definitions/move.h"
#include "../definitions/moveGeneration.h"

#define hashNone 0
#define hashExact 1
#define hashAlpha 2
#define hashBeta 3

#define ttSize (0x100000 * 128)

struct ttEntry{
    ull key;
    int move;
    int depth;
    int flags;
    int value;
};

struct HashTable{
    ttEntry *pTable;
    int numEntries;
    int newWrite;
    int overWrite;
    int hit;
    int cut;
};

void storeTT(ull key, int depth, int value, int hashFlag, ttEntry *tt);
void initHashTable(HashTable *tt);
void clearHashTable(HashTable *tt);
void storeHash(Board *brd, HashTable *tt, int move, int value, int flags, int depth);
bool probeHashTable(Board *brd, HashTable *tt, int *move, int *value, int alpha, int beta, int depth);
int getPvLine(Board *brd, HashTable *tt, int depth);

#endif
