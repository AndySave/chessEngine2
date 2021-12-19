
#ifndef CHESSENGINE2_SLIDERSATTACKS_H
#define CHESSENGINE2_SLIDERSATTACKS_H

#include "../definitions/std_typedef.h"
#include "../utils/bitops.h"

ull generateOccupancy(ull attackMask, int index);

ull incrementalBishopAttack(ull occ, int sq);
ull incrementalRookAttack(ull occ, int sq);

ull bishopAttackRay(ull occ, int sq);
ull rookAttackRay(ull occ, int sq);

void initBishopAttackMasks();
void initRookAttackMasks();

void fillBishopAttacksArray();
void fillRookAttacksArray();

inline ull bishopAttackMasks[64];
inline ull rookAttackMasks[64];
extern ull bishopAttacks[64][512];
extern ull rookAttacks[64][4096];


/// ------------ Relevant bits ------------ ///
inline ull relevantBishopBits[64] = {
        6, 5, 5, 5, 5, 5, 5, 6,
        5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 7, 7, 7, 7, 5, 5,
        5, 5, 7, 9, 9, 7, 5, 5,
        5, 5, 7, 9, 9, 7, 5, 5,
        5, 5, 7, 7, 7, 7, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5,
        6, 5, 5, 5, 5, 5, 5, 6
};

inline ull relevantRookBits[64] = {
        12, 11, 11, 11, 11, 11, 11, 12,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        12, 11, 11, 11, 11, 11, 11, 12
};



/// ----------------------------- MAGIC NUMBERS ---------------------------- ///
/// bishop magics from:                                                      ///
/// https://github.com/DOBRO/binbo/blob/master/include/binbo_magic.hrl       ///
///                                                                          ///
/// rook magics from:                                                        ///
/// https://github.com/goutham/magic-bits/blob/master/include/magic_bits.hpp ///

inline ull bishopMagics[64] = {
        0x0002020202020200, 0x0002020202020000, 0x0004010202000000,
        0x0004040080000000, 0x0001104000000000, 0x0000821040000000,
        0x0000410410400000, 0x0000104104104000, 0x0000040404040400,
        0x0000020202020200, 0x0000040102020000, 0x0000040400800000,
        0x0000011040000000, 0x0000008210400000, 0x0000004104104000,
        0x0000002082082000, 0x0004000808080800, 0x0002000404040400,
        0x0001000202020200, 0x0000800802004000, 0x0000800400A00000,
        0x0000200100884000, 0x0000400082082000, 0x0000200041041000,
        0x0002080010101000, 0x0001040008080800, 0x0000208004010400,
        0x0000404004010200, 0x0000840000802000, 0x0000404002011000,
        0x0000808001041000, 0x0000404000820800, 0x0001041000202000,
        0x0000820800101000, 0x0000104400080800, 0x0000020080080080,
        0x0000404040040100, 0x0000808100020100, 0x0001010100020800,
        0x0000808080010400, 0x0000820820004000, 0x0000410410002000,
        0x0000082088001000, 0x0000002011000800, 0x0000080100400400,
        0x0001010101000200, 0x0002020202000400, 0x0001010101000200,
        0x0000410410400000, 0x0000208208200000, 0x0000002084100000,
        0x0000000020880000, 0x0000001002020000, 0x0000040408020000,
        0x0004040404040000, 0x0002020202020000, 0x0000104104104000,
        0x0000002082082000, 0x0000000020841000, 0x0000000000208800,
        0x0000000010020200, 0x0000000404080200, 0x0000040404040400,
        0x0002020202020200
};

inline ull rookMagics[64] = {
        612498416294952992ULL,  2377936612260610304ULL,  36037730568766080ULL,
        72075188908654856ULL,   144119655536003584ULL,   5836666216720237568ULL,
        9403535813175676288ULL, 1765412295174865024ULL,  3476919663777054752ULL,
        288300746238222339ULL,  9288811671472386ULL,     146648600474026240ULL,
        3799946587537536ULL,    704237264700928ULL,      10133167915730964ULL,
        2305983769267405952ULL, 9223634270415749248ULL,  10344480540467205ULL,
        9376496898355021824ULL, 2323998695235782656ULL,  9241527722809755650ULL,
        189159985010188292ULL,  2310421375767019786ULL,  4647717014536733827ULL,
        5585659813035147264ULL, 1442911135872321664ULL,  140814801969667ULL,
        1188959108457300100ULL, 288815318485696640ULL,   758869733499076736ULL,
        234750139167147013ULL,  2305924931420225604ULL,  9403727128727390345ULL,
        9223970239903959360ULL, 309094713112139074ULL,   38290492990967808ULL,
        3461016597114651648ULL, 181289678366835712ULL,   4927518981226496513ULL,
        1155212901905072225ULL, 36099167912755202ULL,    9024792514543648ULL,
        4611826894462124048ULL, 291045264466247688ULL,   83880127713378308ULL,
        1688867174481936ULL,    563516973121544ULL,      9227888831703941123ULL,
        703691741225216ULL,     45203259517829248ULL,    693563138976596032ULL,
        4038638777286134272ULL, 865817582546978176ULL,   13835621555058516608ULL,
        11541041685463296ULL,   288511853443695360ULL,   283749161902275ULL,
        176489098445378ULL,     2306124759338845321ULL,  720584805193941061ULL,
        4977040710267061250ULL, 10097633331715778562ULL, 325666550235288577ULL,
        1100057149646ULL
};


#endif
