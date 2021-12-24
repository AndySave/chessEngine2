#include "move.h"

void printMove(Move &move) {
    int moveVal = move.move;

    string moveFlag;
    switch (moveFlag(moveVal)) {
        case 0:
            moveFlag = "none";
            break;
        case 1:
            moveFlag = "promotion";
            break;
        case 2:
            moveFlag = "en passant";
            break;
        case 3:
            moveFlag = "castling";
            break;
    }

    string promotedPiece;
    switch (promotedPiece(moveVal)) {
        case 0:
            promotedPiece = "knight";
            break;
        case 1:
            promotedPiece = "bishop";
            break;
        case 2:
            promotedPiece = "rook";
            break;
        case 3:
            promotedPiece = "queen";
            break;
    }
    if (moveFlag(moveVal) != 1) promotedPiece = "none";


    cout << "Move: " << sqToAlgebraic(fromSquare(moveVal)) << " -> " << sqToAlgebraic(toSquare(moveVal)) << "\n";
    cout << "Special move: " <<  moveFlag << "\n";
    cout << "Promoted piece: " << promotedPiece << "\n";
    cout << "Score: " << move.score << "\n";
}

void printMovelist(Movelist *lst){
    for (int i = 0; i < lst->count; i++){
        cout << "------- MOVE #" << i+1 << " -------" << endl;
        Move move = lst->moves[i];
        printMove(move);
        cout << "-----------------------" << endl;
    }
}


int findPiece(Board *brd, int sq, int color){
    int piece = -1;
    if (color == white){
        for (int pce = P; pce <= K; pce++){
            if (getBit(brd->bitboards[pce], sq)){
                piece = pce;
                break;
            }
        }
    }else{
        for (int pce = p; pce <= k; pce++){
            if (getBit(brd->bitboards[pce], sq)){
                piece = pce;
                break;
            }
        }
    }

    return piece;
}

void addQuietMove(Movelist *lst, int move){
    lst->moves[lst->count].move = move;
    lst->moves[lst->count].score = 0;
    lst->count++;
}

void addCaptureMove(Movelist *lst, int move){
    lst->moves[lst->count].move = move;
    lst->moves[lst->count].score = mvvlvaScore[getCaptured(move)][getPiece(move)];
    lst->count++;
}

void addEPMove(Movelist *lst, int move){
    lst->moves[lst->count].move = move;
    lst->moves[lst->count].score = 105;
    lst->count++;
}


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


void addPiece(Board *brd, int sq, int piece) {
    int color = (piece <= K) ? white : black;

    setBit(brd->bitboards[piece], sq);
    setBit(brd->occupancies[color], sq);
    setBit(brd->occupancies[both], sq);

    // Hashing piece in key
    hashPiece(piece, sq);

    // Incrementally updating eval values
    addMaterial(piece);
    addPieceTableScore(piece, sq);
}


void clearPiece(Board *brd, int sq, int piece){
    int color = piece <= K ? white : black;

    // Removing piece from all bitboards
    clearBit(brd->bitboards[piece], sq);
    clearBit(brd->occupancies[color], sq);
    clearBit(brd->occupancies[both], sq);


    // Hashing piece out of key
    hashPiece(piece, sq);

    // Incrementally updating eval values
    removeMaterial(piece);
    removePieceTableScore(piece, sq);
}


void movePiece(Board *brd, int fromSq, int toSq, int piece){
    // Find color of piece
    int color = getBit(brd->occupancies[white], fromSq) ? white : black;

    // Find piece type
    //int piece = findPiece(brd, fromSq, color);

    // Removing piece from all bitboards
    clearBit(brd->bitboards[piece], fromSq);
    clearBit(brd->occupancies[color], fromSq);
    clearBit(brd->occupancies[both], fromSq);

    // Adding piece to all bitboards
    setBit(brd->bitboards[piece], toSq);
    setBit(brd->occupancies[color], toSq);
    setBit(brd->occupancies[both], toSq);

    // Hashing out old piece pos
    hashPiece(piece, fromSq);
    // Hashing in new piece pos
    hashPiece(piece, toSq);

    // Incrementally updating eval values
    removePieceTableScore(piece, fromSq);
    addPieceTableScore(piece, toSq);
}

//IMPORTANT: If a move is made and is not legal, it will be undone automatically.
bool makeMove(Board *brd, int move){
    int from = fromSquare(move);
    int to = toSquare(move);
    int promoted = promotedPiece(move);
    int specialMoveFlag = moveFlag(move);
    //int piece = findPiece(brd, from, brd->side);
    int piece = getPiece(move);

    //Updating the history of game (stored in brd)
    brd->history[brd->ply].move = move;
    brd->history[brd->ply].hashKey = brd->hashKey;
    brd->history[brd->ply].fiftyMove = brd->fiftyMove;
    brd->history[brd->ply].enpassantSq = brd->enpassantSq;
    brd->history[brd->ply].castle = brd->castle;

    if (specialMoveFlag == epFlag){
        if (brd->side == white){
            clearPiece(brd, to-8, p);
        }else{
            clearPiece(brd, to+8, P);
        }
    }else if (specialMoveFlag == castleFlag){
        // If move is a castle move, move the rook
        if (brd->side == white){
            if (to == g1){
                movePiece(brd, h1, f1, R);
            }else{
                movePiece(brd, a1, d1, R);
            }
        }else{
            if (to == g8){
                movePiece(brd, h8, f8, r);
            }else{
                movePiece(brd, a8, d8, r);
            }
        }
    }

    // Hashing out old castle rights
    hashCastle(brd->castle);

    // Updating castle rights
    brd->castle &= castlePerm[from];
    brd->castle &= castlePerm[to];

    // Hashing int new castle rights
    hashCastle(brd->castle);


    // Hashing out old enPassant square
    if (brd->enpassantSq != noSq){
        hashEnpassant(brd->enpassantSq);
    }

    brd->enpassantSq = noSq;

    if (piece == P){
        // If piece is a pawn and moved two squares it generates an enPassant square
        // Resetting fiftyMove counter because of pawn move
        brd->fiftyMove = 0;
        if (from - to == -16){
            brd->enpassantSq = from + 8;
        }
        // Hashing in enPassant square
        hashEnpassant(brd->enpassantSq);
    }else if (piece == p){
        // Resetting fiftyMove counter because of pawn move
        brd->fiftyMove = 0;
        if (from - to == 16){
            brd->enpassantSq = from - 8;
        }
        // Hashing in enPassant square
        hashEnpassant(brd->enpassantSq);
    }

    // If piece exists on to square, it must be a capture
    //bool isCapture = getBit(brd->occupancies[both], to);
    int capturedPiece = getCaptured(move);
    if (capturedPiece != noPiece){
        clearPiece(brd, to, capturedPiece);
        // Capture resets fiftyMove counter
        brd->fiftyMove = 0;
    }else{
        brd->fiftyMove++;
    }

    // Updating king pos
    if (piece == K){
        brd->whiteKingPos = to;
    }else if (piece == k){
        brd->blackKingPos = to;
    }

    // Incrementing halfmoves
    brd->ply++;


    movePiece(brd, from, to, piece);

    if (specialMoveFlag == promFlag){

        if (brd->side == white){
            // remove pawn
            clearPiece(brd, to, P);
            promoted += 1;
        }else{
            clearPiece(brd, to, p);
            promoted += 7;
        }

        addPiece(brd, to, promoted);
    }

    // Swapping side to move
    brd->side ^= 1;
    hashSide;


    if (brd->side == white){
        if (isSquareAttacked(brd, brd->blackKingPos, true)){
            undoMove(brd);
            return false;
        }
    }else{
        if (isSquareAttacked(brd, brd->whiteKingPos, false)){
            undoMove(brd);
            return false;
        }
    }

    return true;
}

void undoMove(Board *brd){
    brd->ply--;

    // swapping sides
    brd->side ^= 1;

    int move = brd->history[brd->ply].move;
    int from = fromSquare(move);
    int to = toSquare(move);
    int specialMoveFlag = moveFlag(move);

    // Finding piece type
    //int piece = findPiece(brd, to, brd->side);
    int piece = getPiece(move);

    brd->castle = brd->history[brd->ply].castle;
    brd->fiftyMove = brd->history[brd->ply].fiftyMove;
    brd->enpassantSq = brd->history[brd->ply].enpassantSq;

    if (specialMoveFlag == epFlag){
        if (brd->side == white){
            addPiece(brd, to-8, p);
        }else{
            addPiece(brd, to+8, P);
        }
    }else if (specialMoveFlag == castleFlag){
        // If move is a castle move, move the rook
        if (brd->side == white){
            if (to == g1){
                movePiece(brd, f1, h1, R);
            }else{
                movePiece(brd, d1, a1, R);
            }
        }else{
            if (to == g8){
                movePiece(brd, f8, h8, r);
            }else{
                movePiece(brd, d8, a8, r);
            }
        }
    }

    // Piece will be stored as Pawn in move so we have to change the piece to
    // the promoted piece
    if (specialMoveFlag == promFlag){
        piece = promotedPiece(move);

        if (brd->side == white){
            piece += 1;
        }else{
            piece += 7;
        }
    }

    // Moving piece back
    movePiece(brd, to, from, piece);

    if (piece == K){
        brd->whiteKingPos = from;
    }else if (piece == k){
        brd->blackKingPos = from;
    }

    // Adding back captured piece if move was capture move
    if (getCaptured(move) != noPiece){
        addPiece(brd, to, getCaptured(move));
    }

    if (specialMoveFlag == promFlag){
        if (brd->side == white){
            clearPiece(brd, from, piece);
            addPiece(brd, from, P);
        }else{
            clearPiece(brd, from, piece);
            addPiece(brd, from, p);
        }
    }

    // Reverting back to old hashKey
    brd->hashKey = brd->history[brd->ply].hashKey;
}

// Checks through history array if position has already occurred
bool isRepetition(Board *brd){
    for (int i = brd->ply - brd->fiftyMove; i < brd->ply-1; i++){
        if (brd->hashKey == brd->history[i].hashKey){
            return true;
        }
    }
    return false;
}


