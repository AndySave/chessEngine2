#ifndef CHESSENGINE2_EVAL_FUNCTIONS_H
#define CHESSENGINE2_EVAL_FUNCTIONS_H

#include "../definitions/std_typedef.h"
#include "../definitions/board.h"
#include "../definitions/slidersAttacks.h"
#include "../definitions/nonSlidersAttacks.h"

inline int numOfPieces; // Number of pieces found on the evaluated board

//Square of all present pieces on the board. The number of present pieces is found in numOfPieces
inline int presentPieces[32];

inline int pieceOfSquare[64]; // Which piece is on which square, use index to check

// How many squares can a piece on index [0,63] reach?
// A square is counted only if: The square has either no pieces or a piece of opposite color.
inline int mobility[64];

// Masks where a piece on index [0,63] can move.
inline ull mobilityMasks[64];

void initMobility(Board* brd);

#endif //CHESSENGINE2_EVAL_FUNCTIONS_H
