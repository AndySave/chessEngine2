
#ifndef CHESSENGINE2_HELPERS_H
#define CHESSENGINE2_HELPERS_H

#include <string>
#include "../definitions/std_typedef.h"
#include <windows.h>



int charToPiece(char c);
char pieceToChar(int piece);
int algebraicToSq(string &coords);
string sqToAlgebraic(int sq);
int getTime();

#endif
