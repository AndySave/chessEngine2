
#ifndef CHESSENGINE2_FEN_H
#define CHESSENGINE2_FEN_H

#include "../definitions/board.h"
#include "../utils/bitops.h"
#include "../definitions/zobristKey.h"
#include "helpers.h"
#include <string>

void FEN(Board *brd, const string &fenStr);

#endif
