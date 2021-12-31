

#ifndef CHESSENGINE2_MOBILITY_H
#define CHESSENGINE2_MOBILITY_H

#include "../definitions/std_typedef.h"
#include "../definitions/board.h"
#include "../definitions/slidersAttacks.h"
#include "../definitions/nonSlidersAttacks.h"
#include "eval_functions.h"

constexpr int mobilityBonus[5][28][2] = {
        {},
        { {-75,-76}, {-56,-54}, {-9,-26}, {-2,-10}, {6,  5}, {15, 11}, // Knights
                {22, 26}, {30, 28}, {36, 29} },

        { {-48,-58}, {-21,-19}, {16, -2}, {26, 12}, {37, 22}, {51, 42}, // Bishops
                {54, 54}, {63, 58}, {65, 63}, {71, 70}, {79, 74}, {81, 86},
                {92, 90}, {97, 94} },

        { {-56,-78}, {-25,-18}, {-11, 26}, {-5, 55}, {-4, 70}, {-1, 81}, // Rooks
                {8,109}, {14,120}, {21,128}, {23,143}, {31,154}, {32,160},
                {43,165}, {49,168}, {59,169} },

        { {-40,-35}, {-25,-12}, {2,  7}, {4, 19}, {14, 37}, {24, 55}, // Queens
                {25, 62}, {40, 76}, {43, 79}, {47, 87}, {54, 94}, {56,102},
                {60,111}, {70,116}, {72,118}, {73,122}, {75,128}, {77,130},
                {85,133}, {94,136}, {99,140}, {108,157}, {112,158}, {113,161},
                {118,174}, {119,177}, {123,191}, {128,199} }
};

inline int midMobility;
inline int endMobility;

void mobilityEvaluation(Board *brd);


#endif //CHESSENGINE2_MOBILITY_H
