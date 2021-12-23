
#ifndef CHESSENGINE2_MOVE_ORDERING_H
#define CHESSENGINE2_MOVE_ORDERING_H

#include "../definitions/std_typedef.h"

/// --------------------VALUES-------------------- ///
inline constexpr int victimScore[12] = {100, 200, 300, 400, 500, 600, 100, 200, 300, 400, 500, 600};
extern int mvvlvaScore[12][12];

/// --------------------INIT FUNCTIONS-------------------- ///
void initMvvLva();

#endif
