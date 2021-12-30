#ifndef CHESSENGINE2_UCI_H
#define CHESSENGINE2_UCI_H

#include <iostream>
#include <cstring>

#include "../utils/bitops.h"
#include "../definitions/nonSlidersAttacks.h"
#include "../definitions/slidersAttacks.h"
#include "../definitions/zobristKey.h"
#include "../utils/fen.h"
#include "../definitions/board.h"
#include "../definitions/moveGeneration.h"
#include "../evaluation/mainEvaluation.h"
#include "../evaluation/pieceTables.h"
#include "../search/move_ordering.h"
#include "../search/main_search.h"

#define INPUT_BUFFER 4096
#define ENGINE_NAME "Humu v2"
#define AUTHOR "AndySave & ask-r0"
#define INITIAL_DEPTH 12
#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

inline int algebraicMoveToInt(char* charPtr, Board* board) {
    if(charPtr[1] > '8' || charPtr[1] < '1') return 0;
    if(charPtr[3] > '8' || charPtr[3] < '1') return 0;
    if(charPtr[0] > 'h' || charPtr[0] < 'a') return 0;
    if(charPtr[2] > 'h' || charPtr[2] < 'a') return 0;
    //createMove(int fromSq, int toSq, int promotedPiece, int moveFlag, int piece, int capturedPiece)
    //findPiece

    string fromAlgebraic;
    fromAlgebraic.push_back(charPtr[0]);
    fromAlgebraic.push_back(charPtr[1]);
    string toAlgebraic;
    toAlgebraic.push_back(charPtr[2]);
    toAlgebraic.push_back(charPtr[3]);


    int fromSq = algebraicToSq(fromAlgebraic);
    int toSq = algebraicToSq(toAlgebraic);

    int promotedPiece;
    int moveFlag = 0;
    if (charPtr[4] == 'n') {
        promotedPiece = 0;
        moveFlag = promFlag;
    } else if (charPtr[4] == 'b') {
        promotedPiece = 1;
        moveFlag = promFlag;
    } else if (charPtr[4] == 'r') {
        promotedPiece = 2;
        moveFlag = promFlag;
    }  else if (charPtr[4] == 'q') {
        promotedPiece = 3;
        moveFlag = promFlag;
    } else {
        promotedPiece = 0;
    }

    //check if it is en passant
    if (board->enpassantSq != noSq) moveFlag = epFlag;

    //check if it is castling
    if (board->whiteKingPos == fromSq && abs(charPtr[3]-charPtr[1]) > 1 ) moveFlag = castleFlag;
    if (board->blackKingPos == fromSq && abs(charPtr[3]-charPtr[1]) > 1 ) moveFlag = castleFlag;

    int piece = findPiece(board, fromSq, board->side);
    int capturedPiece = findPiece(board, toSq, board->side ^ 1);

    return createMove(fromSq, toSq, promotedPiece, moveFlag, piece, capturedPiece);
}

inline string intToAlgebraicMove(int move) {
    string algebraicMove;
    algebraicMove += sqToAlgebraic(fromSquare(move));
    algebraicMove += sqToAlgebraic(toSquare(move));

    if (moveFlag(move) == promFlag) {
        if (promotedPiece(move) == 0) {
            algebraicMove += 'n';
        } else if (promotedPiece(move) == 1) {
            algebraicMove += 'b';
        } else if (promotedPiece(move) == 2) {
            algebraicMove += 'r';
        } else if (promotedPiece(move) == 3) {
            algebraicMove += 'q';
        }
    }
    return algebraicMove;
}

void uci();


#endif
