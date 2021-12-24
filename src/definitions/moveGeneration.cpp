
#include "moveGeneration.h"

// TODO: When generateMoves add capture moves it should store the captured piece somewhere
// which will then be used in the makeMove function. This might help improve speed


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
                    addQuietMove(lst, createMove(pawnPos, pawnPos+8, 0, promFlag));
                    addQuietMove(lst, createMove(pawnPos, pawnPos+8, 1, promFlag));
                    addQuietMove(lst, createMove(pawnPos, pawnPos+8, 2, promFlag));
                    addQuietMove(lst, createMove(pawnPos, pawnPos+8, 3, promFlag));
                }else{
                    addQuietMove(lst, createMove(pawnPos, pawnPos+8, 0, noFlag));
                }

                // Checking if pawn hasn't moved, if so it can move up two squares
                if (rank == 1 && !getBit(occ, pawnPos+16)){
                    addQuietMove(lst, createMove(pawnPos, pawnPos+16, 0, noFlag));
                }
            }

            ull attacks = whitePawnAttacks[pawnPos] & brd->occupancies[black];
            int index;
            while (attacks){
                index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, black);

                if (rank == 6){
                    addCaptureMove(lst, createMove(pawnPos, index, 0, promFlag), P, captured);
                    addCaptureMove(lst, createMove(pawnPos, index, 1, promFlag), P, captured);
                    addCaptureMove(lst, createMove(pawnPos, index, 2, promFlag), P, captured);
                    addCaptureMove(lst, createMove(pawnPos, index, 3, promFlag), P, captured);
                }else{
                    addCaptureMove(lst, createMove(pawnPos, index, 0, noFlag), P, captured);
                }
            }

            if (brd->enpassantSq != noSq && getBit(whitePawnAttacks[pawnPos], brd->enpassantSq)){
                addEPMove(lst, createMove(pawnPos, brd->enpassantSq, 0, epFlag));
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

            addQuietMove(lst, createMove(brd->whiteKingPos, index, 0, noFlag));
        }

        // Handling capture moves
        while (attacks){
            int index = getLSB(attacks);
            clearBit(attacks, index);

            int captured = findPiece(brd, index, black);

            addCaptureMove(lst, createMove(brd->whiteKingPos, index, 0, noFlag), K, captured);
        }

        // Handling castling
        // Checking if we have castle rights first because isSquareAttacked is expensive
        if (WKC & brd->castle || WQC & brd->castle){
            if (!isSquareAttacked(brd, brd->whiteKingPos, false)){
                // Checking that we have castle rights and squares between king and rook are empty
                if (WKC & brd->castle && !getBit(occ, f1) && !getBit(occ, g1)){
                    // Checking if squares between king and rook is under attack
                    if (!isSquareAttacked(brd, f1, false) && !isSquareAttacked(brd, g1, false)){
                        addQuietMove(lst, createMove(brd->whiteKingPos, g1, 0, castleFlag));
                    }
                }
                // Checking that we have castle rights and squares between king and rook are empty
                if (WQC & brd->castle && !getBit(occ, d1) && !getBit(occ, c1) && !getBit(occ, b1)){
                    // Checking if squares between king and rook is under attack
                    if (!isSquareAttacked(brd, d1, false) && !isSquareAttacked(brd, c1, false)){
                        addQuietMove(lst, createMove(brd->whiteKingPos, c1, 0, castleFlag));
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

                addQuietMove(lst, createMove(knightPos, index, 0, noFlag));
            }

            // Handle capture moves
            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, black);

                addCaptureMove(lst, createMove(knightPos, index, 0, noFlag), K, captured);
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

                addQuietMove(lst, createMove(bishopPos, index, 0, noFlag));
            }

            // Handle capture moves
            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, black);

                addCaptureMove(lst, createMove(bishopPos, index, 0, noFlag), B, captured);
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

                addQuietMove(lst, createMove(rookPos, index, 0, noFlag));
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, black);

                addCaptureMove(lst, createMove(rookPos, index, 0, noFlag), R, captured);
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

                addQuietMove(lst, createMove(queenPos, index, 0, noFlag));
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, black);

                addCaptureMove(lst, createMove(queenPos, index, 0, noFlag), Q, captured);
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
                    addQuietMove(lst, createMove(pawnPos, pawnPos-8, 0, promFlag));
                    addQuietMove(lst, createMove(pawnPos, pawnPos-8, 1, promFlag));
                    addQuietMove(lst, createMove(pawnPos, pawnPos-8, 2, promFlag));
                    addQuietMove(lst, createMove(pawnPos, pawnPos-8, 3, promFlag));
                }else{
                    addQuietMove(lst, createMove(pawnPos, pawnPos-8, 0, noFlag));
                }

                // Checking if pawn hasn't moved, if so it can move up two squares
                if (rank == 6 && !getBit(occ, pawnPos-16)){
                    addQuietMove(lst, createMove(pawnPos, pawnPos-16, 0, noFlag));
                }
            }

            ull attacks = blackPawnAttacks[pawnPos] & brd->occupancies[white];
            int index;
            while (attacks){
                index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, white);

                if (rank == 1){
                    addCaptureMove(lst, createMove(pawnPos, index, 0, promFlag), p, captured);
                    addCaptureMove(lst, createMove(pawnPos, index, 1, promFlag), p, captured);
                    addCaptureMove(lst, createMove(pawnPos, index, 2, promFlag), p, captured);
                    addCaptureMove(lst, createMove(pawnPos, index, 3, promFlag), p, captured);
                }else{
                    addCaptureMove(lst, createMove(pawnPos, index, 0, noFlag), p, captured);
                }
            }

            if (brd->enpassantSq != noSq && getBit(blackPawnAttacks[pawnPos], brd->enpassantSq)){
                addEPMove(lst, createMove(pawnPos, brd->enpassantSq, 0, epFlag));
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

            addQuietMove(lst, createMove(brd->blackKingPos, index, 0, noFlag));
        }

        // Handling capture moves
        while (attacks){
            int index = getLSB(attacks);
            clearBit(attacks, index);

            int captured = findPiece(brd, index, white);

            addCaptureMove(lst, createMove(brd->blackKingPos, index, 0, noFlag), k, captured);
        }

        // Handling castling
        // Checking if we have castle rights first because isSquareAttacked is expensive
        if (BKC & brd->castle || BQC & brd->castle){
            if (!isSquareAttacked(brd, brd->blackKingPos, true)){
                // Checking that we have castle rights and squares between king and rook are empty
                if (BKC & brd->castle && !getBit(occ, f8) && !getBit(occ, g8)){
                    // Checking if squares between king and rook is under attack
                    if (!isSquareAttacked(brd, f8, true) && !isSquareAttacked(brd, g8, true)){
                        addQuietMove(lst, createMove(brd->blackKingPos, g8, 0, castleFlag));
                    }
                }
                // Checking that we have castle rights and squares between king and rook are empty
                if (BQC & brd->castle && !getBit(occ, d8) && !getBit(occ, c8) && !getBit(occ, b8)){
                    // Checking if squares between king and rook is under attack
                    if (!isSquareAttacked(brd, d8, true) && !isSquareAttacked(brd, c8, true)){
                        addQuietMove(lst, createMove(brd->blackKingPos, c8, 0, castleFlag));
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

                addQuietMove(lst, createMove(knightPos, index, 0, noFlag));
            }

            // Handle capture moves
            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, white);

                addCaptureMove(lst, createMove(knightPos, index, 0, noFlag), n, captured);
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

                addQuietMove(lst, createMove(bishopPos, index, 0, noFlag));
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, white);

                addCaptureMove(lst, createMove(bishopPos, index, 0, noFlag), b, captured);
            }
        }

        /// ROOK MOVES ///
        ull rookPositions = brd->bitboards[r];
        while (rookPositions){
            int rookPos = getLSB(rookPositions);
            clearBit(rookPositions, rookPos);

            // Getting moves and removing self captures
            ull moves = rookAttackRay(occ, rookPos) & (~brd->occupancies[black]);
            // Getting attacks from moves
            ull attacks = moves & brd->occupancies[white];
            // Removing attacks from quiet moves
            moves &= ~brd->occupancies[white];

            // Handle quiet moves
            while (moves){
                int index = getLSB(moves);
                clearBit(moves, index);

                addQuietMove(lst, createMove(rookPos, index, 0, noFlag));
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, white);

                addCaptureMove(lst, createMove(rookPos, index, 0, noFlag), r, captured);
            }
        }

        /// QUEEN MOVES ///
        ull queenPositions = brd->bitboards[q];
        while (queenPositions){
            int queenPos = getLSB(queenPositions);
            clearBit(queenPositions, queenPos);

            // Getting moves and removing self captures
            ull moves = queenAttackRay(occ, queenPos) & (~brd->occupancies[black]);
            // Getting attacks from moves
            ull attacks = moves & brd->occupancies[white];
            // Removing attacks from quiet moves
            moves &= ~brd->occupancies[white];

            // Handle quiet moves
            while (moves){
                int index = getLSB(moves);
                clearBit(moves, index);

                addQuietMove(lst, createMove(queenPos, index, 0, noFlag));
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, white);

                addCaptureMove(lst, createMove(queenPos, index, 0, noFlag), q, captured);
            }
        }
    }
}
/*
 * Fills a movelist with moves given current board state.
 * Note: Function generates pseudo legal moves.
 */
void generateCaptureMoves(Board *brd, Movelist *lst) {
    lst->count = 0;
    bool side = brd->side;
    ull occ = brd->occupancies[both];

    //Generating capture moves of: PAWN.
    if (side == white) {
        ull pawnPositions = brd->bitboards[P];

        while (pawnPositions) { //Loops through each pawn of current side
            int curPos = getLSB(pawnPositions); //The position of current pawn being evaluated
            clearBit(pawnPositions, curPos);

            ull attacks =  whitePawnAttacks[curPos] & brd->occupancies[black]; //The square current pawn attacks

            int rank = curPos/8; //rank of current pawn

            while(attacks) { //Loops thorugh each square current pawn attacks
                int curAttack = getLSB(attacks);
                clearBit(attacks, curAttack);

                int captured = findPiece(brd, curAttack, black);

                if (rank == 6) { //When a white pawn is on 7th rank and attacks a piece, it promotes too.
                    addCaptureMove(lst, createMove(curPos, curAttack, 0, promFlag), P, captured);
                    addCaptureMove(lst, createMove(curPos, curAttack, 1, promFlag), P, captured);
                    addCaptureMove(lst, createMove(curPos, curAttack, 2, promFlag), P, captured);
                    addCaptureMove(lst, createMove(curPos, curAttack, 3, promFlag), P, captured);
                } else { //When the pawn is not on 7th rank it does not promote, only capture.
                    addCaptureMove(lst, createMove(curPos, curAttack, 0, noFlag), P, captured);
                }
            }

            //Checks if an en passant move is possible. This moves always captures a pawn.
            if (brd->enpassantSq != noSq && getBit(whitePawnAttacks[curPos], brd->enpassantSq)){
                addEPMove(lst, createMove(curPos, brd->enpassantSq, 0, epFlag));
            }
        }
    } else {
        ull pawnPositions = brd->bitboards[p];

        while (pawnPositions) { //Loops through each pawn of current side
            int curPos = getLSB(pawnPositions); //The position of current pawn being evaluated
            clearBit(pawnPositions, curPos);

            ull attacks =  blackPawnAttacks[curPos] & brd->occupancies[white]; //The square current pawn attacks

            int rank = curPos/8; //rank of current pawn

            while(attacks) { //Loops through each square current pawn attacks
                int curAttack = getLSB(attacks);
                clearBit(attacks, curAttack);

                int captured = findPiece(brd, curAttack, white);

                if (rank == 1) { //When a white pawn is on 2nd rank and attacks a piece, it promotes too.
                    addCaptureMove(lst, createMove(curPos, curAttack, 0, promFlag), p, captured);
                    addCaptureMove(lst, createMove(curPos, curAttack, 1, promFlag), p, captured);
                    addCaptureMove(lst, createMove(curPos, curAttack, 2, promFlag), p, captured);
                    addCaptureMove(lst, createMove(curPos, curAttack, 3, promFlag), p, captured);
                } else { //When the pawn is not on 2nd rank it does not promote, only capture.
                    addCaptureMove(lst, createMove(curPos, curAttack, 0, noFlag), p, captured);
                }
            }

            //Checks if an en passant move is possible. This moves always captures a pawn.
            if (brd->enpassantSq != noSq && getBit(blackPawnAttacks[curPos], brd->enpassantSq)){
                addEPMove(lst, createMove(curPos, brd->enpassantSq, 0, epFlag));
            }
        }
    }


    //Generating capture moves of: KING.
    int piece = side ? k : K;
    ull kingPositions = brd->bitboards[piece];

    while (kingPositions) { //Loops through each king of current side
        int curPos = getLSB(kingPositions); //The position of current king being evaluated
        clearBit(kingPositions, curPos);

        ull attacks = kingAttacks[curPos] & brd->occupancies[!side];

        while(attacks) { //Loops through each square current king attacks
            int curAttack = getLSB(attacks);
            clearBit(attacks, curAttack);

            int captured = findPiece(brd, curAttack, !side);

            addCaptureMove(lst, createMove(curPos, curAttack, 0, noFlag), piece, captured);
        }
    }

    //Generating capture moves of: BISHOP.
    piece = side ? b : B;
    ull bishopPositions = brd->bitboards[piece];

    while (bishopPositions) { //Loops through each bishop of current side
        int curPos = getLSB(bishopPositions); //The position of current bishop being evaluated
        clearBit(bishopPositions, curPos);

        ull attacks = bishopAttackRay(occ, curPos) & brd->occupancies[!side];

        while(attacks) { //Loops through each square current bishop attacks
            int curAttack = getLSB(attacks);
            clearBit(attacks, curAttack);

            int captured = findPiece(brd, curAttack, !side);

            addCaptureMove(lst, createMove(curPos, curAttack, 0, noFlag), piece, captured);
        }
    }

    //Generating capture moves of: ROOK.
    piece = side ? r : R;
    ull rookPositions = brd->bitboards[piece];

    while (rookPositions) { //Loops through each rook of current side
        int curPos = getLSB(rookPositions); //The position of current rook being evaluated
        clearBit(rookPositions, curPos);

        ull attacks = rookAttackRay(occ, curPos) & brd->occupancies[!side];

        while(attacks) { //Loops through each square current rook attacks
            int curAttack = getLSB(attacks);
            clearBit(attacks, curAttack);

            int captured = findPiece(brd, curAttack, !side);

            addCaptureMove(lst, createMove(curPos, curAttack, 0, noFlag), piece, captured);
        }
    }

    //Generating capture moves of: KNIGHT.
    piece = side ? n : N;
    ull knightPositions = brd->bitboards[piece];

    while (knightPositions){ //Loops through each knight of current side
        int curPos = getLSB(knightPositions); //The position of current knight being evaluated
        clearBit(knightPositions, curPos);

        ull attacks = knightAttacks[curPos] & brd->occupancies[!side];

        while (attacks){ //Loops through each square current knight attacks
            int curAttack = getLSB(attacks);
            clearBit(attacks, curAttack);

            int captured = findPiece(brd, curAttack, !side);

            addCaptureMove(lst, createMove(curPos, curAttack, 0, noFlag), piece, captured);
        }
    }

    //Generating capture moves of: QUEEN.
    piece = side ? q : Q;
    ull queenPositions = brd->bitboards[piece];

    while (queenPositions){ //Loops through each queen of current side
        int curPos = getLSB(queenPositions); //The position of current queen being evaluated
        clearBit(queenPositions, curPos);

        ull attacks = queenAttackRay(occ, curPos) & brd->occupancies[!side];

        while (attacks){ //Loops through each square current queen attacks
            int curAttack = getLSB(attacks);
            clearBit(attacks, curAttack);

            int captured = findPiece(brd, curAttack, !side);

            addCaptureMove(lst, createMove(curPos, curAttack, 0, noFlag), piece, captured);
        }
    }
}



