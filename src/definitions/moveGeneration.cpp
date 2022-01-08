
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
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos+8, 0, promFlag, P, noPiece));
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos+8, 1, promFlag, P, noPiece));
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos+8, 2, promFlag, P, noPiece));
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos+8, 3, promFlag, P, noPiece));
                }else{
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos+8, 0, noFlag, P, noPiece));
                }

                // Checking if pawn hasn't moved, if so it can move up two squares
                if (rank == 1 && !getBit(occ, pawnPos+16)){
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos+16, 0, noFlag, P, noPiece));
                }
            }

            ull attacks = whitePawnAttacks[pawnPos] & brd->occupancies[black];
            int index;
            while (attacks){
                index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, black);

                if (rank == 6){
                    addCaptureMove(lst, createMove(pawnPos, index, 0, promFlag, P, captured));
                    addCaptureMove(lst, createMove(pawnPos, index, 1, promFlag, P, captured));
                    addCaptureMove(lst, createMove(pawnPos, index, 2, promFlag, P, captured));
                    addCaptureMove(lst, createMove(pawnPos, index, 3, promFlag, P, captured));
                }else{
                    addCaptureMove(lst, createMove(pawnPos, index, 0, noFlag, P, captured));
                }
            }

            if (brd->enpassantSq != noSq && getBit(whitePawnAttacks[pawnPos], brd->enpassantSq)){
                addEPMove(lst, createMove(pawnPos, brd->enpassantSq, 0, epFlag, P, noPiece));
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

            addQuietMove(brd, lst, createMove(brd->whiteKingPos, index, 0, noFlag, K, noPiece));
        }

        // Handling capture moves
        while (attacks){
            int index = getLSB(attacks);
            clearBit(attacks, index);

            int captured = findPiece(brd, index, black);

            addCaptureMove(lst, createMove(brd->whiteKingPos, index, 0, noFlag, K, captured));
        }

        // Handling castling
        // Checking if we have castle rights first because isSquareAttacked is expensive
        if (WKC & brd->castle || WQC & brd->castle){
            if (!isSquareAttacked(brd, brd->whiteKingPos, false)){
                // Checking that we have castle rights and squares between king and rook are empty
                if (WKC & brd->castle && !getBit(occ, f1) && !getBit(occ, g1)){
                    // Checking if squares between king and rook is under attack
                    if (!isSquareAttacked(brd, f1, false) && !isSquareAttacked(brd, g1, false)){
                        addQuietMove(brd, lst, createMove(brd->whiteKingPos, g1, 0, castleFlag, K, noPiece));
                    }
                }
                // Checking that we have castle rights and squares between king and rook are empty
                if (WQC & brd->castle && !getBit(occ, d1) && !getBit(occ, c1) && !getBit(occ, b1)){
                    // Checking if squares between king and rook is under attack
                    if (!isSquareAttacked(brd, d1, false) && !isSquareAttacked(brd, c1, false)){
                        addQuietMove(brd, lst, createMove(brd->whiteKingPos, c1, 0, castleFlag, K, noPiece));
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

                addQuietMove(brd, lst, createMove(knightPos, index, 0, noFlag, N, noPiece));
            }

            // Handle capture moves
            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, black);

                addCaptureMove(lst, createMove(knightPos, index, 0, noFlag, N, captured));
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

                addQuietMove(brd, lst, createMove(bishopPos, index, 0, noFlag, B, noPiece));
            }

            // Handle capture moves
            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, black);

                addCaptureMove(lst, createMove(bishopPos, index, 0, noFlag, B, captured));
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

                addQuietMove(brd, lst, createMove(rookPos, index, 0, noFlag, R, noPiece));
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, black);

                addCaptureMove(lst, createMove(rookPos, index, 0, noFlag, R, captured));
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

                addQuietMove(brd, lst, createMove(queenPos, index, 0, noFlag, Q, noPiece));
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, black);

                addCaptureMove(lst, createMove(queenPos, index, 0, noFlag, Q, captured));
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
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos-8, 0, promFlag, p, noPiece));
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos-8, 1, promFlag, p, noPiece));
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos-8, 2, promFlag, p, noPiece));
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos-8, 3, promFlag, p, noPiece));
                }else{
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos-8, 0, noFlag, p, noPiece));
                }

                // Checking if pawn hasn't moved, if so it can move up two squares
                if (rank == 6 && !getBit(occ, pawnPos-16)){
                    addQuietMove(brd, lst, createMove(pawnPos, pawnPos-16, 0, noFlag, p, noPiece));
                }
            }

            ull attacks = blackPawnAttacks[pawnPos] & brd->occupancies[white];
            int index;
            while (attacks){
                index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, white);

                if (rank == 1){
                    addCaptureMove(lst, createMove(pawnPos, index, 0, promFlag, p, captured));
                    addCaptureMove(lst, createMove(pawnPos, index, 1, promFlag, p, captured));
                    addCaptureMove(lst, createMove(pawnPos, index, 2, promFlag, p, captured));
                    addCaptureMove(lst, createMove(pawnPos, index, 3, promFlag, p, captured));
                }else{
                    addCaptureMove(lst, createMove(pawnPos, index, 0, noFlag, p, captured));
                }
            }

            if (brd->enpassantSq != noSq && getBit(blackPawnAttacks[pawnPos], brd->enpassantSq)){
                addEPMove(lst, createMove(pawnPos, brd->enpassantSq, 0, epFlag, p, noPiece));
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

            addQuietMove(brd, lst, createMove(brd->blackKingPos, index, 0, noFlag, k, noPiece));
        }

        // Handling capture moves
        while (attacks){
            int index = getLSB(attacks);
            clearBit(attacks, index);

            int captured = findPiece(brd, index, white);

            addCaptureMove(lst, createMove(brd->blackKingPos, index, 0, noFlag, k, captured));
        }

        // Handling castling
        // Checking if we have castle rights first because isSquareAttacked is expensive
        if (BKC & brd->castle || BQC & brd->castle){
            if (!isSquareAttacked(brd, brd->blackKingPos, true)){
                // Checking that we have castle rights and squares between king and rook are empty
                if (BKC & brd->castle && !getBit(occ, f8) && !getBit(occ, g8)){
                    // Checking if squares between king and rook is under attack
                    if (!isSquareAttacked(brd, f8, true) && !isSquareAttacked(brd, g8, true)){
                        addQuietMove(brd, lst, createMove(brd->blackKingPos, g8, 0, castleFlag, k, noPiece));
                    }
                }
                // Checking that we have castle rights and squares between king and rook are empty
                if (BQC & brd->castle && !getBit(occ, d8) && !getBit(occ, c8) && !getBit(occ, b8)){
                    // Checking if squares between king and rook is under attack
                    if (!isSquareAttacked(brd, d8, true) && !isSquareAttacked(brd, c8, true)){
                        addQuietMove(brd, lst, createMove(brd->blackKingPos, c8, 0, castleFlag, k, noPiece));
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

                addQuietMove(brd, lst, createMove(knightPos, index, 0, noFlag, n, noPiece));
            }

            // Handle capture moves
            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, white);

                addCaptureMove(lst, createMove(knightPos, index, 0, noFlag, n, captured));
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

                addQuietMove(brd, lst, createMove(bishopPos, index, 0, noFlag, b, noPiece));
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, white);

                addCaptureMove(lst, createMove(bishopPos, index, 0, noFlag, b, captured));
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

                addQuietMove(brd, lst, createMove(rookPos, index, 0, noFlag, r, noPiece));
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, white);

                addCaptureMove(lst, createMove(rookPos, index, 0, noFlag, r, captured));
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

                addQuietMove(brd, lst, createMove(queenPos, index, 0, noFlag, q, noPiece));
            }

            while (attacks){
                int index = getLSB(attacks);
                clearBit(attacks, index);

                int captured = findPiece(brd, index, white);

                addCaptureMove(lst, createMove(queenPos, index, 0, noFlag, q, captured));
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
                    addCaptureMove(lst, createMove(curPos, curAttack, 0, promFlag, P, captured));
                    addCaptureMove(lst, createMove(curPos, curAttack, 1, promFlag, P, captured));
                    addCaptureMove(lst, createMove(curPos, curAttack, 2, promFlag, P, captured));
                    addCaptureMove(lst, createMove(curPos, curAttack, 3, promFlag, P, captured));
                } else { //When the pawn is not on 7th rank it does not promote, only capture.
                    addCaptureMove(lst, createMove(curPos, curAttack, 0, noFlag, P, captured));
                }
            }

            //Checks if an en passant move is possible. This moves always captures a pawn.
            if (brd->enpassantSq != noSq && getBit(whitePawnAttacks[curPos], brd->enpassantSq)){
                addEPMove(lst, createMove(curPos, brd->enpassantSq, 0, epFlag, P, noPiece));
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
                    addCaptureMove(lst, createMove(curPos, curAttack, 0, promFlag, p, captured));
                    addCaptureMove(lst, createMove(curPos, curAttack, 1, promFlag, p, captured));
                    addCaptureMove(lst, createMove(curPos, curAttack, 2, promFlag, p, captured));
                    addCaptureMove(lst, createMove(curPos, curAttack, 3, promFlag, p, captured));
                } else { //When the pawn is not on 2nd rank it does not promote, only capture.
                    addCaptureMove(lst, createMove(curPos, curAttack, 0, noFlag, p, captured));
                }
            }

            //Checks if an en passant move is possible. This moves always captures a pawn.
            if (brd->enpassantSq != noSq && getBit(blackPawnAttacks[curPos], brd->enpassantSq)){
                addEPMove(lst, createMove(curPos, brd->enpassantSq, 0, epFlag, p, noPiece));
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

            addCaptureMove(lst, createMove(curPos, curAttack, 0, noFlag, piece, captured));
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

            addCaptureMove(lst, createMove(curPos, curAttack, 0, noFlag, piece, captured));
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

            addCaptureMove(lst, createMove(curPos, curAttack, 0, noFlag, piece, captured));
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

            addCaptureMove(lst, createMove(curPos, curAttack, 0, noFlag, piece, captured));
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

            addCaptureMove(lst, createMove(curPos, curAttack, 0, noFlag, piece, captured));
        }
    }
}

bool moveExists(Board *brd, int move){
    Movelist moves{};
    generateMoves(brd, &moves);

    for (int count = 0; count < moves.count; count++){
        if (move == moves.moves[count].move){
            return true;
        }
    }

    return false;
}

// Generates a bitboard of all king danger squares.
// Source: https://peterellisjones.com/posts/generating-legal-chess-moves-efficiently/
ull genAttackers(Board* brd, bool isWhiteAttacking) {
    ull attackers = 0;

    if (isWhiteAttacking) {
        ull occ = brd->occupancies[both];
        occ ^= brd->bitboards[k];

        // Loop through each piece
        ull pawnPositions = brd->bitboards[P];
        while (pawnPositions) {
            int curPos = popLsb(&pawnPositions);
            attackers |= whitePawnAttacks[curPos];
        }

        ull knightPositions = brd->bitboards[N];
        while (knightPositions) {
            int curPos = popLsb(&knightPositions);
            attackers |= knightAttacks[curPos];
        }

        ull bishopPositions = brd->bitboards[B];
        while (bishopPositions) {
            int curPos = popLsb(&bishopPositions);
            attackers |= bishopAttackRay(occ, curPos);
        }

        ull rookPositions = brd->bitboards[R];
        while (rookPositions) {
            int curPos = popLsb(&rookPositions);
            attackers |= rookAttackRay(occ, curPos);
        }

        ull queenPositions = brd->bitboards[Q];
        while (queenPositions) {
            int curPos = popLsb(&queenPositions);
            attackers |= queenAttackRay(occ, curPos);
        }

        attackers |= kingAttacks[brd->whiteKingPos];

    } else {
        ull occ = brd->occupancies[both];
        occ ^= brd->bitboards[K];

        // Loop through each piece
        ull pawnPositions = brd->bitboards[p];
        while (pawnPositions) {
            int curPos = popLsb(&pawnPositions);
            attackers |= blackPawnAttacks[curPos];
        }

        ull knightPositions = brd->bitboards[n];
        while (knightPositions) {
            int curPos = popLsb(&knightPositions);
            attackers |= knightAttacks[curPos];
        }

        ull bishopPositions = brd->bitboards[b];
        while (bishopPositions) {
            int curPos = popLsb(&bishopPositions);
            attackers |= bishopAttackRay(occ, curPos);
        }

        ull rookPositions = brd->bitboards[r];
        while (rookPositions) {
            int curPos = popLsb(&rookPositions);
            attackers |= rookAttackRay(occ, curPos);
        }

        ull queenPositions = brd->bitboards[q];
        while (queenPositions) {
            int curPos = popLsb(&queenPositions);
            attackers |= queenAttackRay(occ, curPos);
        }

        attackers |= kingAttacks[brd->blackKingPos];
    }

    return attackers;
}

ull genSquaresBetween(int fromSq, int toSq){
    int downUp[2] = {-1, 1};
    int leftRight[2] = {-1, 1};

    for (int hor : leftRight){
        ull bb = 0ull;
        int file = fromSq % 8, rank = fromSq / 8;
        while (file >= 0 && file < 7){
            file += hor;

            if (file + rank*8 == toSq){
                return bb;
            }
            setBit(bb, file + rank*8);
        }
    }

    for (int vert : downUp){
        ull bb = 0ull;
        int file = fromSq % 8, rank = fromSq / 8;
        while (rank >= 0 && rank < 7){
            rank += vert;

            if (file + rank*8 == toSq){
                return bb;
            }
            setBit(bb, file + rank*8);
        }
    }

    for (int hor : downUp){
        for (int vert : leftRight){
            ull bb = 0ull;
            int file = fromSq % 8, rank = fromSq / 8;
            while (file >= 0 && file < 8 && rank >= 0 && rank < 8){
                file += hor, rank += vert;

                if (file + rank*8 == toSq){
                    return bb;
                }
                setBit(bb, file + rank*8);
            }
        }
    }

    return 0;
}

void initSquaresBetween() {
    for (int i = 0; i<64; i++) {
        for (int j = 0; j<64; j++) {
            squaresBetween[i][j] = genSquaresBetween(i, j);
        }
    }
}

ull genCheckers(Board* brd, bool isWhiteAttacking, int attackedKing) {
    ull checkers = 0;
    ull occ = brd->occupancies[both];

    if (isWhiteAttacking) {
        checkers |= (brd->bitboards[P] & blackPawnAttacks[attackedKing]);
        checkers |= (brd->bitboards[N] & knightAttacks[attackedKing]);
        checkers |= (brd->bitboards[B] & bishopAttackRay(occ, attackedKing));
        checkers |= (brd->bitboards[R] & rookAttackRay(occ, attackedKing));
        checkers |= (brd->bitboards[Q] & queenAttackRay(occ, attackedKing));
    } else {
        checkers |= (brd->bitboards[p] & whitePawnAttacks[attackedKing]);
        checkers |= (brd->bitboards[n] & knightAttacks[attackedKing]);
        checkers |= (brd->bitboards[b] & bishopAttackRay(occ, attackedKing));
        checkers |= (brd->bitboards[r] & rookAttackRay(occ, attackedKing));
        checkers |= (brd->bitboards[q] & queenAttackRay(occ, attackedKing));
    }

    return checkers;
}

void genLegalMoves(Board *brd, Movelist* moves) {

    if (brd->side == white) {
        ull attackers = genAttackers(brd, false);
        ull checkers = genCheckers(brd, false, brd->whiteKingPos);
        int numOfCheckers = sparseCountBits(checkers);

        cout << "Attackers: " << endl; // REPLACE WITH ADDING TO MOVELIST!
        printBitboard(attackers);
        cout << "Checkers: " << endl;
        printBitboard(checkers);

        // KING MOVES
        ull kingMoves = ~attackers & kingAttacks[brd->whiteKingPos] & ~brd->occupancies[white];
        cout << "Available king moves" << endl; // REPLACE WITH ADDING TO MOVELIST!
        while (kingMoves) {
            int curPos = popLsb(&kingMoves);
            cout << sqToAlgebraic(brd->whiteKingPos) << sqToAlgebraic(curPos) << endl; // REPLACE WITH ADDING TO MOVELIST!
        }
        ull captureMask = 0xFFFFFFFFFFFFFFFFull; // Squares a piece can capture on (would be restricted while in check
        ull pushMask = 0xFFFFFFFFFFFFFFFFull; // Squares a piece can move to (would be restricted in case of blocking a check)
        int checkingPiece;

        switch (numOfCheckers) { // Counts the amo
            case 2:
                cout << "Double check." << endl; // REPLACE WITH ADDING TO MOVELIST!
                return; // Only king moves possible
                break;
            case 1:
                cout << "Single check." << endl; // REPLACE WITH ADDING TO MOVELIST!

                // Set captureMask
                captureMask = checkers; // Squares a piece can capture on

                //Set pushMask
                checkingPiece = findPiece(brd, bsf(checkers), black);

                switch (checkingPiece) {
                    case p:
                        pushMask = 0;
                        break;
                    case n:
                        pushMask = 0;
                        break;
                    default:
                        pushMask = squaresBetween[bsf(checkers)][brd->whiteKingPos];
                        break;
                }
                break;
            default:
                cout << "no check." << endl; // REPLACE WITH ADDING TO MOVELIST!
                break;
        }

    } else {


    }
}