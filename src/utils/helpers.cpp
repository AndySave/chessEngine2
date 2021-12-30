
#include "helpers.h"

int charToPiece(char c){
    int piece = -1;
    if (c == 'P'){ piece = P; }
    else if (c == 'N'){ piece = N; }
    else if (c == 'B'){ piece = B; }
    else if (c == 'R'){ piece = R; }
    else if (c == 'Q'){ piece = Q; }
    else if (c == 'K'){ piece = K; }
    else if (c == 'p'){ piece = p; }
    else if (c == 'n'){ piece = n; }
    else if (c == 'b'){ piece = b; }
    else if (c == 'r'){ piece = r; }
    else if (c == 'q'){ piece = q; }
    else if (c == 'k'){ piece = k; }

    if (piece == -1){
        throw "Illegal piece";
    }

    return piece;
}

char pieceToChar(int piece){
    char charPieces[12] = {'P', 'N', 'B', 'R', 'Q', 'K',
                           'p', 'n', 'b', 'r', 'q', 'k'};
    return charPieces[piece];
}

// Example: e3: 20
int algebraicToSq(string &coords){
    int sq = 0;

    char l = coords[0], n = coords[1];
    if (l == 'a'){ sq += 0; }
    if (l == 'b'){ sq += 1; }
    if (l == 'c'){ sq += 2; }
    if (l == 'd'){ sq += 3; }
    if (l == 'e'){ sq += 4; }
    if (l == 'f'){ sq += 5; }
    if (l == 'g'){ sq += 6; }
    if (l == 'h'){ sq += 7; }

    if (n == '1'){ sq += 0; }
    if (n == '2'){ sq += 8; }
    if (n == '3'){ sq += 16; }
    if (n == '4'){ sq += 24; }
    if (n == '5'){ sq += 32; }
    if (n == '6'){ sq += 40; }
    if (n == '7'){ sq += 48; }
    if (n == '8'){ sq += 56; }

    return sq;
}

//Square number to algebraic notation. Example: 0 -> a1
string sqToAlgebraic(int sq) {
    string algebraic;
    algebraic += (char) ((sq % 8) + 'a');
    algebraic += (char) ((sq/8) + '1');

    return algebraic;
}


int getTime(){
    return GetTickCount();
}

int ord(char c){
    return int(c);
}