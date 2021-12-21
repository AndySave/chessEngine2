#ifndef CHESSENGINE2_MOVE_H
#define CHESSENGINE2_MOVE_H

#include "moveStructs.h"
#include <iostream>
#include "std_typedef.h"
#include "../utils/helpers.h"
#include "board.h"
#include "zobristKey.h"
#include "moveGeneration.h"

//Macros to extract information from moveVal (value of a move)
#define fromSquare(move) (move & 0x3f)
#define toSquare(move) ((move >> 6) & 0x3f)
#define promotedPiece(move) ((move >> 12) & 0x3)
#define moveFlag(move) ((move >> 14) & 0x3)

// Used to update castle permissions
const int castlePerm[64] ={
        13, 15, 15, 15, 12, 15, 15, 14,
        15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15,
        7, 15, 15, 15, 3, 15, 15, 11
};


/*
 * Prints a move "move" in a nice format
 */
void printMove(Move& move);

/*
 * Creates a move value (unsigned short) from input fromSq, toSq, promotedPiece and moveFlag.
 */
unsigned short createMove(int fromSq, int toSq, int promotedPiece, int moveFlag);
void addQuietMove(Board *brd, Movelist *lst, unsigned short move);
void addCaptureMove(Board *brd, Movelist *lst, unsigned short move);
void addEPMove(Board *brd, Movelist *lst, unsigned short move);
void addPiece(Board *brd, int sq, int piece);
void clearPiece(Board *brd, int sq);
bool makeMove(Board *brd, unsigned short move);
void undoMove(Board *brd);

#endif

