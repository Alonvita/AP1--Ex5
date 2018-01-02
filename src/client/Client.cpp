//
// Created by alonv on 12/30/2017.
//

#include "Client.h"
#include "../display/Display.h"
#include "../easy_logging/easylogging++.h"

/**
 * Client(string serverIP, int serverPort) initializer.
 *
 * @param serverIP string -- server IP
 * @param serverPort int -- server port
 */
Client::Client(std::string serverIP, int serverPort):
        serverIP(serverIP), serverPort(serverPort), clientSocket(0) {
    clientCreatedAnnouncement();
}

/**
 * connectToServer().
 */
void Client::connectToServer() {
    // Init socket
    this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket >= 0) {

        // Memset the connection details
        memset(&this->connectionDetails, 0, sizeof(this->connectionDetails));
        this->connectionDetails.sin_family = AF_INET;
        this->connectionDetails.sin_addr.s_addr = inet_addr(serverIP.c_str());
        this->connectionDetails.sin_port = htons(serverPort);

        // connect to a server
        if (connect(this->clientSocket,
                    (struct sockaddr *) &this->connectionDetails,
                    sizeof(this->connectionDetails)) >= 0) {

            // message
            socketOpenSuccess();
        } else {
            throw ">> Failure: opening socket.";
        }
    }
}

/**
 * connected().
 */
void Client::connected() {
    // Local Variables
    char msg[MAX_MESSAGE_SIZE] = {0};
    std::string str;
    char dummy;

    // scan the \n from main menu
    scanf("%c", &dummy);

    // read welcome to server message
    read(clientSocket, msg, MAX_MESSAGE_SIZE);


    cout << "Enter a command\n";
    fgets(msg, 1024, stdin);

    str = clearAndCheckString(msg, 255);    // copy message to string
    memset(msg, 0, 1024);                   // clear for reading

    // write message
    write(clientSocket, str.c_str(), str.length()+1);
    memset(msg, 0, 1024);                   // clear for reading

    // read message
    read(clientSocket, msg, 1024);

    cout << msg;

    /*
    while(true) {
        cout << "Enter a command\n";
        fgets(msg, 1024, stdin);

        str = clearAndCheckString(msg, 255);    // copy message to string
        memset(msg, 0, 1024);                   // clear for reading

        // write message
        write(clientSocket, str.c_str(), str.length()+1);

        // read message
        read(clientSocket, msg, 1024);

        str = msg;

        if(strcmp(str.substr(0,11).c_str(), "joined_game") == 0) {
            // print joined game message
            cout << "Successfully joined the game! let's play\n";

            this->color = BLACK;
            myTurn = false;

            LINFO << "BLACK player assigned, going into play() " <<
                                                                 clientSocket;

            play();
            return;
        }

        if(strcmp(str.substr(0,12).c_str(), "game_started") == 0) {
            cout << "Game has started. Please wait for an opponent...\n";

            color = WHITE;
            myTurn = true;

            LINFO << "WHITE player assigned, reading start game message "
                  << clientSocket;
            // read game started message
            readUntil(SINGULAR);
            LINFO << "DONE reading start game message "
                  << clientSocket;

            LINFO << "reading board message " << clientSocket;
            // read board as a message
            readUntil(SINGULAR);
            LINFO << "DONE reading board message " << clientSocket;

            // read available moves
            readUntil(SINGULAR);
            LINFO << "DONE reading board message " << clientSocket;

            LINFO << "going into play(): " << clientSocket;
            play();
            return;
        }

        // print msg
        cout << str;

        // clear for writing
        memset(msg, 0, 1024);
    }*/
}


/**
 * play().
 */
/*void Client::play() {
    // Local Variables
    char msg[1024] = {0};
    std::string str;
    bool gameClosed = false;

    LINFO << clientSocket << ": I AM PLAYING AS " << color;
    LINFO << "myTurn: " << myTurn;

    if (color == BLACK) {
        LINFO << "BLACK player is reading the first board update";
        // updated board
        gameClosed = readUntil(SINGULAR);
    }

    if(gameClosed)
        return;

    do {
        if (!myTurn) {
            LINFO << clientSocket << " player is BLACK";
            // read other player move
            LINFO << clientSocket << " Waiting for player move message";
            gameClosed = readUntil(MOVE_MESSAGE);
            if(gameClosed)
                break;
            LINFO << clientSocket << " Player move message received";

            LINFO << clientSocket <<
                  " Reading singular message - expecting Board update";
            // updated board
            gameClosed = readUntil(SINGULAR);
            if(gameClosed)
                break;
            LINFO << clientSocket <<
                  " DONE Reading singular message - expecting Board update";

            LINFO <<clientSocket << " Waiting for player available moves "
                    "update";
            // read my available moves
            gameClosed = readUntil(PLAYER_MOVED);
            if(gameClosed)
                break;
            LINFO << clientSocket << " Available moves update received";

            // turn starts
            LINFO << "Changing turn status for player" << clientSocket;
            myTurn = true;
        } else {
            do {

                LINFO << clientSocket << " player is WHITE";
                // read from client
                gameClosed = writeAndReadUntil(BOARD_MESSAGE);
                if(gameClosed)
                    break;

                LINFO << "get the board message -- reading the board update"
                      << clientSocket;
                // read board update
                readUntil(SINGULAR);
                LINFO << "DONE get the board message -- reading the board "
                        "update" << clientSocket;

                LINFO << clientSocket << ": reading \"played\"";
                // read "played"
                read(clientSocket, msg, 1024);
                LINFO << clientSocket << ": DONE reading \"played\"";

            } while (strcmp(msg, PLAYER_MOVED) != 0);
            if(gameClosed)
                break;

            // turn ended
            myTurn = false;
        }
    } while(msg != GAME_OVER_MESSAGE);

    // read the game over message
    readUntil(SINGULAR);
}*/

/**
 * readUntil(std::string messageType).
 *
 * This function will help us ignore all incoming server traffic that is
 *  unecessary or may harm the gameplay.
 */
/*bool Client::readUntil(std::string messageType) {
    char msg[1024] = {0};
    char dummy;
    std::string str;

    if(messageType == SINGULAR) {
        LINFO << clientSocket << " is reading a singular message from server";
        // read message
        if(read(clientSocket, msg, 1024) < 1){
            LINFO << "Server was closed";
            return true;
        }

        if(strcmp(msg, GAME_CLOSED_MESSAGE) == 0)
            return true;

        // print message
        cout << msg;

        LINFO << clientSocket << " is  DONE reading a singular message from "
                "server";

        // clear for next operation
        memset(msg, 0, 1024);

        return false;
    } else {
        do {
            // clear for next operation
            memset(msg, 0, 1024);

            LINFO << clientSocket << " is reading a (looped) message from "
                    "server";
            // read message
            if(read(clientSocket, msg, 1024) < 1) {
                LINFO << "Server was closed";
                return true;
            }

            if(strcmp(msg, GAME_CLOSED_MESSAGE) == 0)
                return true;

            if (strcmp(msg, messageType.c_str()) == 0) {
                LDEBUG << "breaking out of loop with message: " << msg;
                break;
            }

            // print message
            cout << msg;

        } while(true);
        LINFO << clientSocket << " is DONE reading a (looped) message from "
                "server";
    }
    // never got a "close" message - return false.
    return false;

}*/

/**
 * scanCommand().
 */
/*void Client::writeCommandToServer() {
    // Local Variables
    char msg[1024];
    std::string str;
    char dummy;

    LINFO << "client: " << clientSocket << " is inside writeCommandToServer ";
    fgets(msg, 1024, stdin);

    str = clearAndCheckString(msg, 255);    // copy message to string
    memset(msg, 0, 1024);                   // clear for reading

    LINFO << "Writing Message: " << str << " by: " << clientSocket <<
            "indice writeCommandToServer";
    // write message
    write(clientSocket, str.c_str(), 1024);
    LINFO << "Message wrote: " << str << " by: " << clientSocket <<
          "indice writeCommandToServer";
}*/

/**
 * readAndWriteUntil(std::string messageType).
 *
 * @param messageType
 */
/*bool Client::writeAndReadUntil(std::string messageType) {
    char msg[1024];
    std::string str;

    do {
        LINFO << clientSocket << " is inside writeAndReadUntil";
        // clear for next operation
        memset(msg, 0, 1024);

        LINFO << clientSocket << " is writing a message to server (looped)";
        // scan command
        cout << "\nMake a move: \n";
        writeCommandToServer();
        LINFO << clientSocket << " is DONE writing a message to server "
                "(looped)";

        LINFO << clientSocket << " reading inside writeAndReadUntil";
        LINFO << clientSocket << " is reading message from server";

        // clear for next operation
        //memset(msg, 0, 1024);

        // read message
        read(clientSocket, msg, 1024);

        if(strcmp(msg, GAME_CLOSED_MESSAGE) == 0)
            return true;

        // print message
        cout << msg;

        LINFO << clientSocket << " is DONE reading message from server";
    } while(strcmp(msg, messageType.c_str()) != 0);

    return false;
}*/