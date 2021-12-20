#ifndef CHESSENGINE2_MOVE_H
#define CHESSENGINE2_MOVE_H

#include <iostream>
#include "std_typedef.h"
#include "../utils/helpers.h"

//Macros to extract information from moveVal (value of a move)
#define fromSquare(move) (move & 0x3f)
#define toSquare(move) ((move >> 6) & 0x3f)
#define promotedPiece(move) ((move >> 12) & 0x3)
#define moveFlag(move) ((move >> 14) & 0x3)

/*
 * A move consists of 16 bits:
 * Bits [1, 2] : Special move flag. 00 = nothing, 01 = promotion, 10 = en passant, 11 = castling
 * Bits [3, 4] : Promoted piece. 00 = knight, 01 = bishop, 10 = rook, 11 = queen
 * Bits [5, 10]: To square. Square piece is being moved to. Value from 0-63 inclusive.
 * Bits [11,16]: From square. Square piece is being moved from. Value from 0-63 inclusive.
 */
struct Move {
    unsigned short move; //The move
    int score;
};

struct Movelist{
    Move moves[512];
    int count;
};

struct Undo{
    int move;
    int castlePerm;
    int enPas;
    int fiftyMove;
    ull posKey;
};

/*
 * Prints a move "move" in a nice format
 */
void printMove(Move& move);

/*
 * Creates a move value (unsigned short) from input fromSq, toSq, promotedPiece and moveFlag.
 */
unsigned short createMove(int fromSq, int toSq, int promotedPiece, int moveFlag);

#endif //CHESSENGINE2_MOVE_H
