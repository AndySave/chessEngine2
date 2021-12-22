
#ifndef CHESSENGINE2_BOARD_H
#define CHESSENGINE2_BOARD_H

#include "std_typedef.h"
#include <iostream>
#include "../utils/bitops.h"
#include "../utils/helpers.h"
#include <bitset>
#include "moveStructs.h"

// Board structure.
struct Board{
    ull bitboards[12]; // Bitboards hold the positioning of pieces. One index for each piece.
    ull occupancies[3]; // Squares occupied by: 0 - white, 1 - black, 2 - both black and white.

    int side; // 0 = white, 1 = black
    int enpassantSq = noSq; //En passant square
    int castle; // Holds the current possibility of castling for black and white

    int ply; // Halfmoves since game started
    int move; // Fullmoves since game started
    int fiftyMove;  // Halfmoves since last capture or pawn move

    int whiteKingPos; // Position of white king
    int blackKingPos; // Position of black king

    ull hashKey = 0ull; // Key of current board state

    Undo history[2048]; // History of previous moves
};

// Prints board in a nice format
void printBoard(Board *brd);

// Resets a board to empty
void cleanBoard(Board *brd);

#endif