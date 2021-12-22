
#ifndef CHESSENGINE2_MAINEVALUATION_H
#define CHESSENGINE2_MAINEVALUATION_H

#include "../definitions/board.h"
#include "../definitions/std_typedef.h"
#include "../utils/bitops.h"


/// --------------------TAPERED VALUES-------------------- ///
constexpr inline int tapered[12] = {0, 1, 1, 2, 4, 0, 0, 1, 1, 2, 4, 0};
// totalPhase = tapered[P]*16 + tapered[K]*4 + tapered[B]*4 + tapered[R]*4 + tapered[Q]*2;
inline int totalPhase = 24;
inline int phase = 0;

/// --------------------PIECE VALUES-------------------- ///
enum values {
    pawnValueMg   = 126,   pawnValueEg   = 208,
    knightValueMg = 781,   knightValueEg = 854,
    bishopValueMg = 825,   bishopValueEg = 915,
    rookValueMg   = 1276,  rookValueEg   = 1380,
    queenValueMg  = 2538,  queenValueEg  = 2682
};



void initPhase(Board *brd);
int eval(Board *brd);


#endif
