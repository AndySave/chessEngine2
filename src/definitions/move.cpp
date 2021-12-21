#include "move.h"

void printMove(Move &move) {
    unsigned short moveVal = move.move;

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


unsigned short createMove(int fromSq, int toSq, int promotedPiece, int moveFlag) {
    return fromSq | (toSq << 6) | (promotedPiece << 12) | (moveFlag << 14);
}

void addPiece(Board *brd, int sq, int piece) {
    int color = (piece <= K) ? white : black;

    setBit(brd->bitboards[piece], sq);
    setBit(brd->occupancies[color], sq);
    setBit(brd->occupancies[both], sq);

    hashPiece(piece, sq);

    // TODO: Add incremental material update and pieceTable update
}


void clearPiece(Board *brd, int sq){
    int color = getBit(brd->occupancies[white], sq) ? white : black;

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

    // Removing piece from all bitboards
    clearBit(brd->bitboards[piece], sq);
    clearBit(brd->occupancies[color], sq);
    clearBit(brd->occupancies[both], sq);


    // Hashing piece out of key
    hashPiece(piece, sq);

    // TODO: Add incremental material update and pieceTable update
}


void movePiece(Board *brd, int fromSq, int toSq){
    // Find color of piece
    int color = getBit(brd->occupancies[white], fromSq) ? white : black;

    // Find piece type
    int piece = -1;
    if (color == white){
        for (int pce = P; pce <= K; pce++){
            if (getBit(brd->bitboards[pce], fromSq)){
                piece = pce;
                break;
            }
        }
    }else{
        for (int pce = p; pce <= k; pce++){
            if (getBit(brd->bitboards[pce], fromSq)){
                piece = pce;
                break;
            }
        }
    }

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

    // TODO: Add incremental material update and pieceTable update
}


// Returns true if move is legal, false otherwise
bool makeMove(Board *brd, unsigned short move){
    int from = fromSquare(move);
    int to = toSquare(move);
    int promoted = promotedPiece(move);
    int specialMoveFlag = moveFlag(move);


    // TODO: Add all info to history array

    if (specialMoveFlag == epFlag){
        if (brd->side == white){
            clearPiece(brd, to-8);
        }else{
            clearPiece(brd, to+8);
        }
    }else if (specialMoveFlag == castleFlag){
        // If move is a castle move, move the rook
        if (brd->side == white){
            if (to == g1){
                movePiece(brd, h1, f1);
            }else{
                movePiece(brd, a1, d1);
            }
        }else{
            if (to == g8){
                movePiece(brd, h8, f8);
            }else{
                movePiece(brd, a8, d8);
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
    if (brd->side == white){
        bool isPawn = getBit(brd->bitboards[P], from);
        // If piece is a pawn and moved two squares it generates an enPassant square
        if (isPawn){
            // Resetting fiftyMove counter because of pawn move
            brd->fiftyMove = 0;
            if (from - to == -16){
                brd->enpassantSq = from + 8;
            }
        }
    }else{
        bool isPawn = getBit(brd->bitboards[p], from);
        if (isPawn){
            // Resetting fiftyMove counter because of pawn move
            brd->fiftyMove = 0;
            if (from - to == 16){
                brd->enpassantSq = from - 8;
            }
        }

        // Hashing in enPassant square
        hashEnpassant(brd->enpassantSq);
    }

    // If piece exists on to square, it must be a capture
    bool isCapture = getBit(brd->occupancies[both], to);
    if (isCapture){
        clearPiece(brd, to);
        // Capture resets fiftyMove counter
        brd->fiftyMove = 0;
    }else{
        brd->fiftyMove++;
    }

    // Updating king pos
    if (brd->side == white){
        if (from == brd->whiteKingPos){
            brd->whiteKingPos = to;
        }
    }else{
        if (from == brd->blackKingPos){
            brd->blackKingPos = to;
        }
    }

    // Incrementing halfmoves
    brd->ply++;


    movePiece(brd, from, to);

    if (specialMoveFlag == promFlag){
        // remove pawn
        clearPiece(brd, to);

        // incrementing promoted piece to match piece values
        promoted++;
        if (brd->side == black){
            promoted += 6;
        }
        // add promoted piece
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

}
