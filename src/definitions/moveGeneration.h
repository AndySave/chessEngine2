
#ifndef CHESSENGINE2_MOVEGENERATION_H
#define CHESSENGINE2_MOVEGENERATION_H

#include "nonSlidersAttacks.h"
#include "board.h"
#include "slidersAttacks.h"
#include "std_typedef.h"
#include <iostream>
#include "moveStructs.h"
#include "move.h"

// Squares between [from][to]
inline ull squaresBetween[64][64];

// Squares between [from][to] and extending past to
inline ull squaresBetweenRay[64][64];

void generateMoves(Board *brd, Movelist *lst);
void generateCaptureMoves(Board *brd, Movelist *lst);
bool moveExists(Board *brd, int move);

ull genAttackers(Board* brd, bool isWhiteAttacking);

ull genCheckers(Board* brd, bool isWhiteAttacking, int attackedKing);

void genLegalMoves(Board *brd, Movelist* moves);

void initSquaresBetween();
void initSquaresBetweenRay();



#endif
