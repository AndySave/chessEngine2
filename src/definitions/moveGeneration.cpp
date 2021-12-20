
#include "moveGeneration.h"

bool isSquareAttacked(Board *brd, int sq, bool whiteAttacking){
    ull occ = brd->occupancies[both];
    if (whiteAttacking){
        if (bishopAttackRay(occ, sq) & (brd->bitboards[B] | brd->bitboards[Q])){
            return true;
        }
        if (rookAttackRay(occ, sq) & (brd->bitboards[R] | brd->bitboards[Q])){
            return true;
        }
        if (knightAttacks[sq] & brd->bitboards[N]){
            return true;
        }
        if (kingAttacks[sq] & brd->bitboards[K]){
            return true;
        }
        if (blackPawnAttacks[sq] & brd->bitboards[P]){
            return true;
        }

    }else{
        if (bishopAttackRay(occ, sq) & (brd->bitboards[b] | brd->bitboards[q])){
            return true;
        }
        if (rookAttackRay(occ, sq) & (brd->bitboards[r] | brd->bitboards[q])){
            return true;
        }
        if (knightAttacks[sq] & brd->bitboards[n]){
            return true;
        }
        if (kingAttacks[sq] & brd->bitboards[k]){
            return true;
        }
        if (whitePawnAttacks[sq] & brd->bitboards[p]){
            return true;
        }
    }

    return false;
}

// Prints representation of the board where attacked squares are 'X' and if not '.'
void printAttackedSquares(Board *brd, bool whiteAttacking){
    for (int rank = 7; rank >= 0; rank--){
        cout << rank+1 << "  ";
        for (int file = 0; file < 8; file++){
            int sq = rank*8 + file;
            if (isSquareAttacked(brd, sq, whiteAttacking)){
                cout << "X ";
            }else{
                cout << ". ";
            }

        }
        cout << endl;
    }

    cout << endl << "   ";
    for (int i = 0; i < 8; i++){
        cout << char(97+i) << " ";
    }
    cout << endl;
}


/*
void generateMoves(Board *brd){
    ull occ = brd->occupancies[both];
    if (brd->side == white){

        ull bb = brd->bitboards[P];

        while (bb){
            int index = getLSB(bb);
            clearBit(bb, index);

            int rank = index/8;
            if (!getBit(occ, index+8)){

                if (rank == 6){
                    // Generate pawn promotion
                }else{
                    // Generate pawn quiet move
                }

                if (rank == 2 && !getBit(index+16)){
                    // Generate pawn quiet move and add enPassant square
                }
            }
        }

    }
}

*/




