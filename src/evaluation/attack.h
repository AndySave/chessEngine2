#ifndef CHESSENGINE2_ATTACK_H
#define CHESSENGINE2_ATTACK_H

#include "../definitions/std_typedef.h"
#include "../definitions/board.h"
#include "../definitions/slidersAttacks.h"
#include "../definitions/nonSlidersAttacks.h"

inline int kingSafetyEval;
inline int midMobilityEval;
inline int endMobilityEval;

inline ull whiteKingZones[64];
inline ull blackKingZones[64];

// Attack units for pieces, how much they value a piece has as a attacker on opponent king zone.
//                              {P, N, B, R, Q, K, p, n, b, r, q, k, noPiece}
constexpr int attackUnits[13] = {0, 2, 2, 3, 5, 0, 0, 2, 2, 3, 5, 0, 0};

constexpr int safetyTable[100] = {
        0,  0,   1,   2,   3,   5,   7,   9,  12,  15,
        18,  22,  26,  30,  35,  39,  44,  50,  56,  62,
        68,  75,  82,  85,  89,  97, 105, 113, 122, 131,
        140, 150, 169, 180, 191, 202, 213, 225, 237, 248,
        260, 272, 283, 295, 307, 319, 330, 342, 354, 366,
        377, 389, 401, 412, 424, 436, 448, 459, 471, 483,
        494, 500, 500, 500, 500, 500, 500, 500, 500, 500,
        500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
        500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
        500, 500, 500, 500, 500, 500, 500, 500, 500, 500
};

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

//Initialization method, must be called before callubg mobilityEval.
void initKingZones();

/*
 * King safety and mobility evaluation
 */
void mobilityEval(Board* brd);

#endif //CHESSENGINE2_ATTACK_H
