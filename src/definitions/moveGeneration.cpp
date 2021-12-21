
#include "moveGeneration.h"


void generateMoves(Board *brd, Movelist *lst){
    lst->count = 0;

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
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos+8, N, promFlag));
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos+8, B, promFlag));
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos+8, R, promFlag));
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos+8, Q, promFlag));
                }else{
                    cout << "Pawn quiet move  : " << pawnPos << " -> " << pawnPos+8 << endl;
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos+8, 0, noFlag));
                }

                // Checking if pawn hasn't moved, if so it can move up two squares
                if (rank == 1 && !getBit(occ, pawnPos+16)){
                    cout << "Pawn quiet move  : " << pawnPos << " -> " << pawnPos+16 << endl;
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos+16, 0, noFlag));
                }
            }

            ull attacks = whitePawnAttacks[pawnPos] & brd->occupancies[black];
            int index;
            while (attacks){
                index = getLSB(attacks);
                clearBit(attacks, index);

                if (index == brd->enpassantSq){
                    cout << "Pawn EP move: " << pawnPos << " -> " << index << endl;
                    addEPMove(brd, lst, createMove(pawnPos, index, 0, epFlag));
                }else{
                    cout << "Pawn capture move: " << pawnPos << " -> " << index << endl;
                    addCaptureMove(brd, lst, createMove(pawnPos, index, 0, noFlag));
                }
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
            addQuietMove(brd, lst, createMove(brd->whiteKingPos, index, 0, noFlag));
        }

        // Handling capture moves
        while (attacks){
            int index = getLSB(attacks);
            clearBit(attacks, index);

            cout << "King capture move: " << brd->whiteKingPos << " -> " << index << endl;
            addCaptureMove(brd, lst, createMove(brd->whiteKingPos, index, 0, noFlag));
        }

        // Handling castling
        // Checking if we have castle rights first because isSquareAttacked is expensive
        if (WKC & brd->castle || WQC & brd->castle){
            if (!isSquareAttacked(brd, brd->whiteKingPos, false)){
                // Checking that we have castle rights and squares between king and rook are empty
                if (WKC & brd->castle && !getBit(occ, f1) && !getBit(occ, g1)){
                    // Checking if squares between king and rook is under attack
                    if (!isSquareAttacked(brd, f1, false) && !isSquareAttacked(brd, g1, false)){
                        cout << "King side castle" << endl;
                        addQuietMove(brd, lst, createMove(brd->whiteKingPos, g1, 0, castleFlag));
                    }
                }
                // Checking that we have castle rights and squares between king and rook are empty
                if (WQC & brd->castle && !getBit(occ, d1) && !getBit(occ, c1)){
                    // Checking if squares between king and rook is under attack
                    if (!isSquareAttacked(brd, d1, false) && !isSquareAttacked(brd, c1, false)){
                        cout << "Queen side castle" << endl;
                        addQuietMove(brd, lst, createMove(brd->whiteKingPos, c1, 0, castleFlag));
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
                addQuietMove(brd, lst, createMove(knightPos, index, 0, noFlag));
            }

            // Handle capture moves
            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                cout << "Knight capture move: " << knightPos << " -> " << index << endl;
                addCaptureMove(brd, lst, createMove(knightPos, index, 0, noFlag));
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
                addQuietMove(brd, lst, createMove(bishopPos, index, 0, noFlag));
            }

            // Handle capture moves
            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                cout << "Bishop capture move: " << bishopPos << " -> " << index << endl;
                addCaptureMove(brd, lst, createMove(bishopPos, index, 0, noFlag));
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
                addQuietMove(brd, lst, createMove(rookPos, index, 0, noFlag));
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                cout << "Rook capture move: " << rookPos << " -> " << index << endl;
                addCaptureMove(brd, lst, createMove(rookPos, index, 0, noFlag));
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
                addQuietMove(brd, lst, createMove(queenPos, index, 0, noFlag));
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                cout << "Queen capture move: " << queenPos << " -> " << index << endl;
                addCaptureMove(brd, lst, createMove(queenPos, index, 0, noFlag));
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
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos-8, n, promFlag));
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos-8, b, promFlag));
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos-8, r, promFlag));
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos-8, q, promFlag));
                }else{
                    cout << "Pawn quiet move  : " << pawnPos << " -> " << pawnPos-8 << endl;
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos-8, 0, noFlag));
                }

                // Checking if pawn hasn't moved, if so it can move up two squares
                if (rank == 6 && !getBit(occ, pawnPos-16)){
                    cout << "Pawn quiet move  : " << pawnPos << " -> " << pawnPos-16 << endl;
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos-16, 0, noFlag));
                }
            }

            ull attacks = blackPawnAttacks[pawnPos] & brd->occupancies[white];
            int index;
            while (attacks){
                index = getLSB(attacks);
                clearBit(attacks, index);

                if (index == brd->enpassantSq){
                    cout << "Pawn EP move: " << pawnPos << " -> " << index << endl;
                    addEPMove(brd, lst, createMove(pawnPos, index, 0, epFlag));
                }else{
                    cout << "Pawn capture move: " << pawnPos << " -> " << index << endl;
                    addCaptureMove(brd, lst, createMove(pawnPos, index, 0, noFlag));
                }
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
            addQuietMove(brd, lst, createMove(brd->blackKingPos, index, 0, noFlag));
        }

        // Handling capture moves
        while (attacks){
            int index = getLSB(attacks);
            clearBit(attacks, index);

            cout << "King capture move: " << brd->blackKingPos << " -> " << index << endl;
            addCaptureMove(brd, lst, createMove(brd->blackKingPos, index, 0, noFlag));
        }

        // Handling castling
        // Checking if we have castle rights first because isSquareAttacked is expensive
        if (BKC & brd->castle || BQC & brd->castle){
            if (!isSquareAttacked(brd, brd->blackKingPos, true)){
                // Checking that we have castle rights and squares between king and rook are empty
                if (BKC & brd->castle && !getBit(occ, f8) && !getBit(occ, g8)){
                    // Checking if squares between king and rook is under attack
                    if (!isSquareAttacked(brd, f8, true) && !isSquareAttacked(brd, g8, true)){
                        cout << "King side castle" << endl;
                        addQuietMove(brd, lst, createMove(brd->blackKingPos, g8, 0, castleFlag));
                    }
                }
                // Checking that we have castle rights and squares between king and rook are empty
                if (BQC & brd->castle && !getBit(occ, d8) && !getBit(occ, c8)){
                    // Checking if squares between king and rook is under attack
                    if (!isSquareAttacked(brd, d8, true) && !isSquareAttacked(brd, c8, true)){
                        cout << "Queen side castle" << endl;
                        addQuietMove(brd, lst, createMove(brd->blackKingPos, c8, 0, castleFlag));
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
                addQuietMove(brd, lst, createMove(knightPos, index, 0, noFlag));
            }

            // Handle capture moves
            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                cout << "Knight capture move: " << knightPos << " -> " << index << endl;
                addCaptureMove(brd, lst, createMove(knightPos, index, 0, noFlag));
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
                addQuietMove(brd, lst, createMove(bishopPos, index, 0, noFlag));
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                cout << "Bishop capture move: " << bishopPos << " -> " << index << endl;
                addCaptureMove(brd, lst, createMove(bishopPos, index, 0, noFlag));
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
                addQuietMove(brd, lst, createMove(rookPos, index, 0, noFlag));
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                cout << "Rook capture move: " << rookPos << " -> " << index << endl;
                addCaptureMove(brd, lst, createMove(rookPos, index, 0, noFlag));
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
                addQuietMove(brd, lst, createMove(queenPos, index, 0, noFlag));
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                cout << "Queen capture move: " << queenPos << " -> " << index << endl;
                addCaptureMove(brd, lst, createMove(queenPos, index, 0, noFlag));
            }
        }
    }
}



