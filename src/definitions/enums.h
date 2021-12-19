
#ifndef CHESSENGINE2_ENUMS_H
#define CHESSENGINE2_ENUMS_H


enum color {white, black, both};
enum pieces {e, P, N, B, R, Q, K, p, n, b, r, q, k};
enum castle {WKC = 1, WQC = 2, BKC = 4, BQC = 8};

enum squares {
    a1, a2, a3, a4, a5, a6, a7, a8,
    b1, b2, b3, b4, b5, b6, b7, b8,
    c1, c2, c3, c4, c5, c6, c7, c8,
    d1, d2, d3, d4, d5, d6, d7, d8,
    e1, e2, e3, e4, e5, e6, e7, e8,
    f1, f2, f3, f4, f5, f6, f7, f8,
    g1, g2, g3, g4, g5, g6, g7, g8,
    h1, h2, h3, h4, h5, h6, h7, h8
};

ull files[8] = {0x0101010101010101, 0x0202020202020202, 0x0404040404040404, 0x0808080808080808,
                0x1010101010101010, 0x2020202020202020, 0x4040404040404040, 0x8080808080808080};
ull ranks[8] = {0xFF, 0xFF00, 0xFF0000, 0xFF000000, 0xFF00000000, 0xFF0000000000, 0xFF000000000000, 0xFF00000000000000};


#endif
