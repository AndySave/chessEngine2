
#ifndef CHESSENGINE2_MAINEVALUATION_H
#define CHESSENGINE2_MAINEVALUATION_H

#include "../definitions/board.h"
#include "../definitions/std_typedef.h"
#include "../utils/bitops.h"
#include "../definitions/nonSlidersAttacks.h"
#include "../definitions/slidersAttacks.h"
#include "pieceTables.h"
#include "mobility.h"


/// --------------------TAPERED VALUES-------------------- ///
inline int phase = 0;
// totalPhase = tapered[P]*16 + tapered[K]*4 + tapered[B]*4 + tapered[R]*4 + tapered[Q]*2;
inline int totalPhase = 24;
inline int taperedFactor = 256;
constexpr inline int tapered[12] = {0, 1, 1, 2, 4, 0, 0, 1, 1, 2, 4, 0};

/// --------------------PIECE VALUES-------------------- ///
inline int materialMG = 0;
inline int materialEG = 0;
constexpr inline int pieceValuesMg[12] = {126, 781, 825, 1276, 2538, 0, 126, 781, 825, 1276, 2538, 0};
constexpr inline int pieceValuesEg[12] = {208, 854, 915, 1380, 2681, 0, 208, 854, 915, 1380, 2681, 0};

/// --------------------INIT FUNCTIONS-------------------- ///
void initPhase(Board *brd);
void initMaterial(Board *brd);

/// --------------------UPDATE VALUE FUNCTIONS-------------------- ///
void addMaterial(int piece);
void removeMaterial(int piece);
void addPhase(int piece);
void removePhase(int piece);

/// --------------------MAIN FUNCTIONS-------------------- ///
int eval(Board *brd);


#endif
