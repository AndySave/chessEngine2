
#include "board_utils.h"

void printBoard(Board *brd){

    string out;
    for (int sq = 0; sq < 64; sq++){
        bool noPiece = true;
        for (int pce = 0; pce < 12; pce++){
            ull bb = brd->bitboards[pce];

            if (getBit(bb, sq)){
                noPiece = false;
                out += pieceToChar(pce);
            }
        }

        if (noPiece){ out += '.'; }
    }

    for (int rank = 7; rank >= 0; rank--){
        cout << rank+1 << "  ";
        for (int file = 0; file < 8; file++){
            cout << out[rank*8 + file] << " ";
        }
        cout << endl;
    }

    cout << endl << "   ";
    for (int i = 0; i < 8; i++){
        cout << char(97+i) << " ";
    }
    cout << endl;

    cout << "Key: " << brd->hashKey << endl;
    cout << "Side: " << (brd->side ? 'b' : 'w') << endl;

    if (brd->enpassantSq == 64){ cout << "Enpassant: noSq" << endl; }
    else{ cout << "Enpassant: " << brd->enpassantSq << endl; }

    cout << "Castle: " << bitset<4>(brd->castle) << endl;
}
