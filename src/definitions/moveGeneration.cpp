
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


void generateMoves(Board *brd){
    ull occ = brd->occupancies[both];
    if (brd->side == white){


        /// PAWN MOVES ///
        ull pawnPositions = brd->bitboards[P];
        while (pawnPositions){
            int pawnPos = getLSB(pawnPositions);
            clearBit(pawnPositions, pawnPos);

            int rank = pawnPos/8;
            if (!getBit(occ, pawnPos+8)){
                if (rank == 6){
                    cout << "Pawn promotion: " << pawnPos << " -> " << pawnPos+8 << endl;
                }else{
                    cout << "Pawn quiet move  : " << pawnPos << " -> " << pawnPos+8 << endl;
                }

                // Checking if pawn hasn't moved, if so it can move up two squares
                if (rank == 1 && !getBit(occ, pawnPos+16)){
                    // Add en passant square
                    cout << "Pawn quiet move  : " << pawnPos << " -> " << pawnPos+16 << endl;
                }
            }

            ull attacks = whitePawnAttacks[pawnPos] & brd->occupancies[black];
            int index;
            while (attacks){
                index = getLSB(attacks);
                clearBit(attacks, index);

                cout << "Pawn capture move: " << pawnPos << " -> " << index << endl;
            }
        }

        /// KING MOVES ///
        // Getting moves and removing self captures
        ull moves = kingAttacks[brd->whiteKingPos] & (~brd->occupancies[white]);
        // Extracting attacks from moves
        ull attacks = moves & brd->occupancies[black];
        // Removing attacks from quiet moves
        moves &= ~brd->occupancies[black];

        // Handling quiet moves
        while (moves){
            int index = getLSB(moves);
            clearBit(moves, index);

            cout << "King quiet move: " << brd->whiteKingPos << " -> " << index << endl;
        }

        // Handling capture moves
        while (attacks){
            int index = getLSB(attacks);
            clearBit(attacks, index);

            cout << "King capture move: " << brd->whiteKingPos << " -> " << index << endl;
        }

        // Handling castling
        // Checking if we have castle rights first because isSquareAttacked is expensive
        if (WKC & brd->castle || WQC & brd->castle){
            if (!isSquareAttacked(brd, brd->whiteKingPos, false)){
                // Checking that we have castle rights and squares between king and rook are empty
                if (WKC & brd->castle && !getBit(occ, 5) && !getBit(occ, 6)){
                    // Checking if squares between king and rook is under attack
                    if (!isSquareAttacked(brd, 5, false) && !isSquareAttacked(brd, 6, false)){
                        cout << "King side castle" << endl;
                    }
                }
                // Checking that we have castle rights and squares between king and rook are empty
                if (WQC & brd->castle && !getBit(occ, 3) && !getBit(occ, 2)){
                    // Checking if squares between king and rook is under attack
                    if (!isSquareAttacked(brd, 3, false) && !isSquareAttacked(brd, 2, false)){
                        cout << "Queen side castle" << endl;
                    }
                }
            }
        }

        /// BISHOP MOVES ///
        ull bishopPositions = brd->bitboards[B];
        while (bishopPositions){
            int bishopPos = getLSB(bishopPositions);
            clearBit(bishopPositions, bishopPos);

            ull moves = bishopAttackRay(occ, bishopPos) & (~brd->occupancies[white]);;
            ull attacks = moves & brd->occupancies[black];
            moves &= ~brd->occupancies[black];
        }

        /// ROOK MOVES ///

        /// QUEEN MOVES ///
    }
}



