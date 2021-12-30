#include "uci.h"

void preInit() {
    initBitMasks();
    initWhitePawnAttacks();
    initBlackPawnAttacks();
    initKnightAttacks();
    initKingAttacks();
    initBishopAttackMasks();
    initRookAttackMasks();

    initHashkeys();

    initMvvLva();

    fillBishopAttacksArray();
    fillRookAttacksArray();
}

void postInit(Board* board) {
    initPhase(board);
    initMaterial(board);
    initPieceTable(board);
}

void allInit(Board* board) {
    preInit();
    postInit(board);
}

bool isCommand(const char* line, const char *command) {
    int n = strlen(command);
    if (!strncmp(line, command, n)) {
        return true;
    }
    return false;
}

void commandUCI() {
    cout << "id name " << ENGINE_NAME << endl;
    cout << "id author " << AUTHOR << endl;
    cout << "uciok" << endl;
}

void commandIsReady() {
    cout << "readyok" << endl;
}

void commandUCINewGame(Board* board, HashTable* tt) {
    allInit(board);
    initHashTable(tt);
}

void commandPosition(char* line, Board *board) {
    line += 9; //increment pointer past "position "
    char *charPtr = line;

    if (isCommand(line, "startpos")) {
        FEN(board, START_FEN);
    } else {
        charPtr = strstr(line, "fen");
        if (charPtr == NULL) { //fen not found in line
            FEN(board, START_FEN);
        } else {
            charPtr += 4;
            FEN(board, charPtr);
        }

    }

    charPtr = strstr(line, "moves");

    if(charPtr != NULL) {
        charPtr += 6;
        while(*charPtr) {
            int move = algebraicMoveToInt(charPtr, board);
            if(move == 0) break;
            makeMove(board, move);

            while(*charPtr && *charPtr!= ' ') charPtr++;
            charPtr++;
        }
    }
}

void commandGo(char* line, SearchInfo* info, Board* board, HashTable* tt) {
    int depth = -1, movestogo = 30,movetime = -1;
    int time = -1, inc = 0;
    char *ptr = NULL;
    info->timeSet = false;

    if ((ptr = strstr(line,"infinite"))) {
        //ignore
    }

    if ((ptr = strstr(line,"binc")) && board->side == black) {
        inc = atoi(ptr + 5);
    }

    if ((ptr = strstr(line,"winc")) && board->side == white) {
        inc = atoi(ptr + 5);
    }

    if ((ptr = strstr(line,"wtime")) && board->side == white) {
        time = atoi(ptr + 6);
    }

    if ((ptr = strstr(line,"btime")) && board->side == black) {
        time = atoi(ptr + 6);
    }

    if ((ptr = strstr(line,"movestogo"))) {
        movestogo = atoi(ptr + 10);
    }

    if ((ptr = strstr(line,"movetime"))) {
        movetime = atoi(ptr + 9);
    }

    if ((ptr = strstr(line,"depth"))) {
        depth = atoi(ptr + 6);
    }

    if(movetime != -1) {
        time = movetime;
        movestogo = 1;
    }

    info->startTime = getTime();

    if(time != -1) {
        info->timeSet = TRUE;
        time /= movestogo;
        time -= 50;
        info->stopTime = info->startTime + time + inc;
    }

    if(depth == -1) {
        depth = 12; //temporary, based on time later
    }

    info->depth = depth;

    printf("time:%d start:%d stop:%d depth:%d timeset:%d\n",
           time,info->startTime,info->stopTime,info->depth,info->timeSet);

    cout << info->depth << endl;
    search(board, tt, info->depth);

    cout << "bestmove " << intToAlgebraicMove(probePvMove(board, tt)) << endl;
}

void commandQuit(SearchInfo* info) {
    info->quit = true;
}


/*
Commands UCI -> Engine:

- uci
- isready
- ucinewgame
- position
- go
- stop
- quit

Commands Engine -> UCI:
- uciok
- readyok
- bestmove
- info
 */
void uci() {
    Board board;
    SearchInfo searchInfo;
    searchInfo.depth = 12;
    allInit(&board);

    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    char line[INPUT_BUFFER];

    HashTable tt{};
    initHashTable(&tt);

    while (true) {
        memset(&line[0], 0, sizeof(line));
        fflush(stdout);

        if (!fgets(line, INPUT_BUFFER, stdin)) continue;
        if (line[0] == '\n') continue;

        if (isCommand(line, "ucinewgame")) {
            commandUCINewGame(&board, &tt);

        } else if (isCommand(line, "uci")) {
            commandUCI();

        }  else if (isCommand(line, "isready")) {
            commandIsReady();

        } else if (isCommand(line, "position")) {
            commandPosition(line, &board);
            printBoard(&board);

        } else if (isCommand(line, "go")) {
            commandGo(line, &searchInfo, &board, &tt);
        } else if (isCommand(line, "stop")) {
            //ignore

        } else if (isCommand(line, "quit")) {
            commandQuit(&searchInfo);
        }

        if (searchInfo.quit) break;
    }
}
