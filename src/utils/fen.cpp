
#include "fen.h"

void cleanBoard(Board *brd){
    for (ull &bitboard : brd->bitboards){
        bitboard = 0ull;
    }

    for (ull &occupancy : brd->occupancies){
        occupancy = 0ull;
    }

    brd->side = white;
    brd->enpassantSq = noSq;
    brd->castle = 0;
    brd->ply = 0;
    brd->move = 1;
    brd->hashKey = 0ull;
}


void FEN(Board *brd, const string &fenStr){

    // Resets the board values
    cleanBoard(brd);

    vector<string> components;
    int lastSpace = -1;
    for (int i = 0; i < fenStr.length(); i++){
        if (fenStr[i] == ' '){
            string s;
            for (int j = lastSpace+1; j < i; j++){
                s += fenStr[j];
            }

            components.push_back(s);
            lastSpace = i;
        }
    }

    string s;
    for (int i = lastSpace+1; i < fenStr.length(); i++){
        s += fenStr[i];
    }
    components.push_back(s);

    string piecePlacement = components[0];
    string sideToMove = components[1];
    string castleRights = components[2];
    string enpassantSquare = components[3];
    string halfmove = components[4];
    string fullmove = components[5];

    int file = 0, rank = 7;
    for (int i = 0; i < piecePlacement.length(); i++){
        int sq = file + rank*8;
        if (piecePlacement[i] == '/'){
            rank--;
            file = 0;
        }else if (isdigit(piecePlacement[i])){
            file += piecePlacement[i] - '0';
        }else{
            int piece = charToPiece(piecePlacement[i]);

            // Placing piece on board
            setBit(brd->bitboards[piece], sq);

            // Checking if piece is white
            if (piece <= K){
                setBit(brd->occupancies[white], sq);
            }else{
                setBit(brd->occupancies[black], sq);
            }
            setBit(brd->occupancies[both], sq);

            // Updating hash key
            hashPiece(brd->hashKey, piece, sq);

            file++;
        }
    }

    if (sideToMove == "w"){
        hashSide(brd->hashKey);
    }

    if (enpassantSquare != "-"){
        int sq = algebraicToSq(enpassantSquare);
        brd->enpassantSq = sq;
        hashEnpassant(brd->hashKey, sq);
    }

    // Updating castle rights
    for (char c : castleRights){
        if (c == 'K'){ brd->castle += WKC; }
        if (c == 'Q'){ brd->castle += WQC; }
        if (c == 'k'){ brd->castle += BKC; }
        if (c == 'q'){ brd->castle += BQC; }
    }

    // Updating plies since last capture or pawn advance
    brd->ply = stoi(halfmove);

    // Updating move number
    brd->move = stoi(fullmove);
}


