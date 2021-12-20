#include "move.h"

void printMove(Move &move) {
    unsigned short moveVal = move.move;

    string moveFlag;
    switch (moveFlag(moveVal)) {
        case 0:
            moveFlag = "none";
            break;
        case 1:
            moveFlag = "promotion";
            break;
        case 2:
            moveFlag = "en passant";
            break;
        case 3:
            moveFlag = "castling";
            break;
    }

    string promotedPiece;
    switch (promotedPiece(moveVal)) {
        case 0:
            promotedPiece = "knight";
            break;
        case 1:
            promotedPiece = "bishop";
            break;
        case 2:
            promotedPiece = "rook";
            break;
        case 3:
            promotedPiece = "queen";
            break;
    }
    if (moveFlag(moveVal) != 1) promotedPiece = "none";


    cout << "Move: " << sqToAlgebraic(fromSquare(moveVal)) << " -> " << sqToAlgebraic(toSquare(moveVal)) << "\n";
    cout << "Special move: " <<  moveFlag << "\n";
    cout << "Promoted piece: " << promotedPiece << "\n";
    cout << "Score: " << move.score << "\n";
}

unsigned short createMove(int fromSq, int toSq, int promotedPiece, int moveFlag) {
    unsigned short move = 0;
    move |= fromSq;
    move |= (6 << toSq);
    move |= (12 << promotedPiece);
    move |= (14 << moveFlag);

    return move;
}