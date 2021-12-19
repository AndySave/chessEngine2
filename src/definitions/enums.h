
#ifndef CHESSENGINE2_ENUMS_H
#define CHESSENGINE2_ENUMS_H


enum color {white, black, both};
enum pieces {e, P, N, B, R, Q, K, p, n, b, r, q, k};
enum castle {WKC = 1, WQC = 2, BKC = 4, BQC = 8};

enum squares {
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8
};

inline ull files[8] = {0x0101010101010101, 0x0202020202020202, 0x0404040404040404, 0x0808080808080808,
                0x1010101010101010, 0x2020202020202020, 0x4040404040404040, 0x8080808080808080};
inline ull ranks[8] = {0xFF, 0xFF00, 0xFF0000, 0xFF000000, 0xFF00000000,
                       0xFF0000000000, 0xFF000000000000, 0xFF00000000000000};


#endif
