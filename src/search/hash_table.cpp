
#include "hash_table.h"


void clearHashTable(HashTable *tt){
    ttEntry *tableEntry;
    for (tableEntry = tt->pTable; tableEntry < tt->pTable + tt->numEntries; tableEntry++){
        tableEntry->key = 0ull;
        tableEntry->move = 0;
        tableEntry->depth = 0;
        tableEntry->value = 0;
        tableEntry->flags = hashNone;
    }
}

void initHashTable(HashTable *tt){
    tt->numEntries = ttSize / sizeof(ttEntry);
    tt->numEntries -= 2;
    tt->pTable = (ttEntry*) malloc(tt->numEntries * sizeof(ttEntry));
    clearHashTable(tt);
    cout << "Transposition Table initialized with " << tt->numEntries << " entries" << endl;
}


void storeHash(Board *brd, HashTable *tt, int move, int value, int flags, int depth){
    int index = brd->hashKey & tt->numEntries;

    if (tt->pTable[index].key == 0){
        tt->newWrite++;
    }else{
        /*
        if (tt->pTable[index].flags == hashExact && tt->pTable[index].depth >= depth){
            return;
        }
         */

        tt->overWrite++;
    }

    tt->pTable[index].move = move;
    tt->pTable[index].key = brd->hashKey;
    tt->pTable[index].flags = flags;
    tt->pTable[index].value = value;
    tt->pTable[index].depth = depth;
}


bool probeHashTable(Board *brd, HashTable *tt, int *move, int *value, int alpha, int beta, int depth){
    int index = brd->hashKey & tt->numEntries;

    if (tt->pTable[index].key == brd->hashKey){
        *move = tt->pTable[index].move;

        if (tt->pTable[index].depth >= depth){
            tt->hit++;

            *value = tt->pTable[index].value;

            switch (tt->pTable[index].flags){

                case hashAlpha:
                    if (*value <= alpha){
                        *value = alpha;
                        return true;
                    }
                    break;

                case hashBeta:
                    if (*value >= beta){
                        *value = beta;
                        return true;
                    }
                    break;

                case hashExact:
                    return true;
                    break;

                default:
                    break;
            }
        }
    }

    return false;
}


int probePvMove(Board *brd, HashTable *tt){
    int index = brd->hashKey & tt->numEntries;

    if (tt->pTable[index].key == brd->hashKey){
        return tt->pTable[index].move;
    }

    return 0;
}

int getPvLine(Board *brd, HashTable *tt, int depth){
    int move = probePvMove(brd, tt);
    int count = 0;

    while (move != 0 && count < depth){
        if (moveExists(brd, move)){
            makeMove(brd, move);
            brd->pvTable[count] = move;
            count++;
        }

        move = probePvMove(brd, tt);
    }

    for (int i = 0; i < count; i++){
        undoMove(brd);
    }

    return count;
}

