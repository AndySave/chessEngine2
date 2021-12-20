
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
        /// -----WHITE MOVE GEN----- ///

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
        // Getting attacks from moves
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

        /// KNIGHT MOVES ///
        ull knightPositions = brd->bitboards[N];
        while (knightPositions){
            int knightPos = getLSB(knightPositions);
            clearBit(knightPositions, knightPos);

            // Getting moves and removing self captures
            ull moves = knightAttacks[knightPos] & (~brd->occupancies[white]);
            // Getting attacks from moves
            ull attacks = moves & brd->occupancies[black];
            // Removing attacks from quiet moves
            moves &= ~brd->occupancies[black];

            // Handle quiet moves
            while (moves){
                int index = getLSB(moves);
                clearBit(moves, index);

                cout << "Knight quiet move: " << knightPos << " -> " << index << endl;
            }

            // Handle capture moves
            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                cout << "Knight capture move: " << knightPos << " -> " << index << endl;
            }
        }

        /// BISHOP MOVES ///
        ull bishopPositions = brd->bitboards[B];
        while (bishopPositions){
            int bishopPos = getLSB(bishopPositions);
            clearBit(bishopPositions, bishopPos);

            // Getting moves and removing self captures
            ull moves = bishopAttackRay(occ, bishopPos) & (~brd->occupancies[white]);
            // Getting attacks from moves
            ull attacks = moves & brd->occupancies[black];
            // Removing attacks from quiet moves
            moves &= ~brd->occupancies[black];

            // Handle quiet moves
            while (moves){
                int index = getLSB(moves);
                clearBit(moves, index);

                cout << "Bishop quiet move: " << bishopPos << " -> " << index << endl;
            }

            // Handle capture moves
            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                cout << "Bishop capture move: " << bishopPos << " -> " << index << endl;
            }
        }

        /// ROOK MOVES ///
        ull rookPositions = brd->bitboards[R];
        while (rookPositions){
            int rookPos = getLSB(rookPositions);
            clearBit(rookPositions, rookPos);

            // Getting moves and removing self captures
            ull moves = rookAttackRay(occ, rookPos) & (~brd->occupancies[white]);;
            // Getting attacks from moves
            ull attacks = moves & brd->occupancies[black];
            // Removing attacks from quiet moves
            moves &= ~brd->occupancies[black];

            // Handle quiet moves
            while (moves){
                int index = getLSB(moves);
                clearBit(moves, index);

                cout << "Rook quiet move: " << rookPos << " -> " << index << endl;
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                cout << "Rook capture move: " << rookPos << " -> " << index << endl;
            }
        }

        /// QUEEN MOVES ///
        ull queenPositions = brd->bitboards[Q];
        while (queenPositions){
            int queenPos = getLSB(queenPositions);
            clearBit(queenPositions, queenPos);

            // Getting moves and removing self captures
            ull moves = queenAttackRay(occ, queenPos) & (~brd->occupancies[white]);;
            // Getting attacks from moves
            ull attacks = moves & brd->occupancies[black];
            // Removing attacks from quiet moves
            moves &= ~brd->occupancies[black];

            // Handle quiet moves
            while (moves){
                int index = getLSB(moves);
                clearBit(moves, index);

                cout << "Queen quiet move: " << queenPos << " -> " << index << endl;
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                cout << "Queen capture move: " << queenPos << " -> " << index << endl;
            }
        }


    }else{
        /// -----BLACK MOVE GEN----- ///

        /// PAWN MOVES ///
        ull pawnPositions = brd->bitboards[p];
        while (pawnPositions){
            int pawnPos = getLSB(pawnPositions);
            clearBit(pawnPositions, pawnPos);

            int rank = pawnPos/8;
            if (!getBit(occ, pawnPos-8)){
                if (rank == 1){
                    cout << "Pawn promotion: " << pawnPos << " -> " << pawnPos-8 << endl;
                }else{
                    cout << "Pawn quiet move  : " << pawnPos << " -> " << pawnPos-8 << endl;
                }

                // Checking if pawn hasn't moved, if so it can move up two squares
                if (rank == 6 && !getBit(occ, pawnPos-16)){
                    // Add en passant square
                    cout << "Pawn quiet move  : " << pawnPos << " -> " << pawnPos-16 << endl;
                }
            }

            ull attacks = blackPawnAttacks[pawnPos] & brd->occupancies[white];
            int index;
            while (attacks){
                index = getLSB(attacks);
                clearBit(attacks, index);

                cout << "Pawn capture move: " << pawnPos << " -> " << index << endl;
            }
        }

        /// KING MOVES ///
        // Getting moves and removing self captures
        ull moves = kingAttacks[brd->blackKingPos] & (~brd->occupancies[black]);
        // Getting attacks from moves
        ull attacks = moves & brd->occupancies[white];
        // Removing attacks from quiet moves
        moves &= ~brd->occupancies[white];

        // Handling quiet moves
        while (moves){
            int index = getLSB(moves);
            clearBit(moves, index);

            cout << "King quiet move: " << brd->blackKingPos << " -> " << index << endl;
        }

        // Handling capture moves
        while (attacks){
            int index = getLSB(attacks);
            clearBit(attacks, index);

            cout << "King capture move: " << brd->blackKingPos << " -> " << index << endl;
        }

        // Handling castling
        // Checking if we have castle rights first because isSquareAttacked is expensive
        if (BKC & brd->castle || BQC & brd->castle){
            if (!isSquareAttacked(brd, brd->blackKingPos, true)){
                // Checking that we have castle rights and squares between king and rook are empty
                if (BKC & brd->castle && !getBit(occ, 61) && !getBit(occ, 62)){
                    // Checking if squares between king and rook is under attack
                    if (!isSquareAttacked(brd, 61, true) && !isSquareAttacked(brd, 62, true)){
                        cout << "King side castle" << endl;
                    }
                }
                // Checking that we have castle rights and squares between king and rook are empty
                if (BQC & brd->castle && !getBit(occ, 59) && !getBit(occ, 58)){
                    // Checking if squares between king and rook is under attack
                    if (!isSquareAttacked(brd, 59, true) && !isSquareAttacked(brd, 58, true)){
                        cout << "Queen side castle" << endl;
                    }
                }
            }
        }

        /// KNIGHT MOVES ///
        ull knightPositions = brd->bitboards[n];
        while (knightPositions){
            int knightPos = getLSB(knightPositions);
            clearBit(knightPositions, knightPos);

            // Getting moves and removing self captures
            ull moves = knightAttacks[knightPos] & (~brd->occupancies[black]);
            // Getting attacks from moves
            ull attacks = moves & brd->occupancies[white];
            // Removing attacks from quiet moves
            moves &= ~brd->occupancies[white];

            // Handle quiet moves
            while (moves){
                int index = getLSB(moves);
                clearBit(moves, index);

                cout << "Knight quiet move: " << knightPos << " -> " << index << endl;
            }

            // Handle capture moves
            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                cout << "Knight capture move: " << knightPos << " -> " << index << endl;
            }
        }

        /// BISHOP MOVES ///
        ull bishopPositions = brd->bitboards[b];
        while (bishopPositions){
            int bishopPos = getLSB(bishopPositions);
            clearBit(bishopPositions, bishopPos);

            // Getting moves and removing self captures
            ull moves = bishopAttackRay(occ, bishopPos) & (~brd->occupancies[black]);;
            // Getting attacks from moves
            ull attacks = moves & brd->occupancies[white];
            // Removing attacks from quiet moves
            moves &= ~brd->occupancies[white];

            // Handle quiet moves
            while (moves){
                int index = getLSB(moves);
                clearBit(moves, index);

                cout << "Bishop quiet move: " << bishopPos << " -> " << index << endl;
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                cout << "Bishop capture move: " << bishopPos << " -> " << index << endl;
            }
        }

        /// ROOK MOVES ///
        ull rookPositions = brd->bitboards[r];
        while (rookPositions){
            int rookPos = getLSB(rookPositions);
            clearBit(rookPositions, rookPos);

            // Getting moves and removing self captures
            ull moves = rookAttackRay(occ, rookPos) & (~brd->occupancies[black]);;
            // Getting attacks from moves
            ull attacks = moves & brd->occupancies[white];
            // Removing attacks from quiet moves
            moves &= ~brd->occupancies[white];

            // Handle quiet moves
            while (moves){
                int index = getLSB(moves);
                clearBit(moves, index);

                cout << "Rook quiet move: " << rookPos << " -> " << index << endl;
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                cout << "Rook capture move: " << rookPos << " -> " << index << endl;
            }
        }

        /// QUEEN MOVES ///
        ull queenPositions = brd->bitboards[q];
        while (queenPositions){
            int queenPos = getLSB(queenPositions);
            clearBit(queenPositions, queenPos);

            // Getting moves and removing self captures
            ull moves = queenAttackRay(occ, queenPos) & (~brd->occupancies[black]);;
            // Getting attacks from moves
            ull attacks = moves & brd->occupancies[white];
            // Removing attacks from quiet moves
            moves &= ~brd->occupancies[white];

            // Handle quiet moves
            while (moves){
                int index = getLSB(moves);
                clearBit(moves, index);

                cout << "Queen quiet move: " << queenPos << " -> " << index << endl;
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                cout << "Queen capture move: " << queenPos << " -> " << index << endl;
            }
        }
    }
}



