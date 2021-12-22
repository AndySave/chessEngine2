#include "pieceTables.h"

/*
 * Initializes values pieceTableScoreMG and pieceTableScoreEG.
 * Must be called after FEN because it need board values
 */
void initPieceTable(Board *brd){
    for (int pce = P; pce <= k; pce++){
        ull piecePositions = brd->bitboards[pce];

        while (piecePositions){
            int piecePos = getLSB(piecePositions);
            clearBit(piecePositions, piecePos);

            addPieceTableScore(pce, piecePos);
        }
    }
}

void addPieceTableScore(int piece, int sq){
    int color = piece <= K ? white : black;
    if (color == white){
        pieceTableScoreMG += pieceTables[piece][sq][0];
        pieceTableScoreEG += pieceTables[piece][sq][1];

    }else{
        pieceTableScoreMG -= pieceTables[piece][getMirror(sq)][0];
        pieceTableScoreEG -= pieceTables[piece][getMirror(sq)][1];
    }
}

void removePieceTableScore(int piece, int sq){
    int color = piece <= K ? white : black;
    if (color == white){
        pieceTableScoreMG -= pieceTables[piece][sq][0];
        pieceTableScoreEG -= pieceTables[piece][sq][1];

    }else{
        pieceTableScoreMG += pieceTables[piece][getMirror(sq)][0];
        pieceTableScoreEG += pieceTables[piece][getMirror(sq)][1];
    }
}
