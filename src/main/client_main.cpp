/**
 * Project:    Ex4.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * Class client_main.
 *
 * Creates a client, connects him to the game and lets him play either
 *  a multi-player or singleplayer game.
 */

#include "../easy_logging/easylogging++.h"
_INITIALIZE_EASYLOGGINGPP

#include "../game/game_flow/Reversi.h"
#include "../client/Client.h"



void printStartingMessage();
void printBoardTypeRequest();

using namespace std;

int main() {
    int gameType;

    printStartingMessage();

    cin >> gameType;

    if (gameType == 3) {
        Client client("127.0.0.1", 8000);
        LINFO << "Connecting to the server...";
        try {
            client.connectToServer();
        } catch (const char *msg) {
            cout << "Failed to connect to server. Reason: " << msg
                 << endl;
            exit(-1);
        }
        client.connected();

    } else if (gameType == 1 || gameType == 2) {
        int boardType;
        printBoardTypeRequest();

        cin >> boardType;

        Reversi g(boardType, gameType);
        g.startGame();
    } else {
        cout << "Bad argument...";
        exit(-1);
    }
}

/**
 * startingMessage().
 */
void printStartingMessage() {
    cout << "Choose an opponent type"       << endl
         << "1. A Human-Local Player"       << endl
         << "2. An AI Player"               << endl
         << "3. A Remote Player"            << endl
         << "Press anything else to quit"   << endl;
}

/**
 * printBoardTypeRequest();
 */
void printBoardTypeRequest() {
    cout << "Please choose a board type"    << endl
         << "1. 6x6 board"                  << endl
         << "2. 8x8 board (also default)"   << endl
         << "3. 10x10 board"                << endl;
}