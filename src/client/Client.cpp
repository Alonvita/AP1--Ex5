//
// Created by alonv on 12/30/2017.
//

#include "Client.h"
#include "../easy_logging/easylogging++.h"

/**
 * Client(string serverIP, int serverPort) initializer.
 *
 * @param serverIP string -- server IP
 * @param serverPort int -- server port
 */
Client::Client(std::string serverIP, int serverPort) {
    this->serverIP = serverIP;
    this->serverPort = serverPort;
    this->clientSocket = -1;
    this->stayConnected = true;
    clientCreatedAnnouncement();
}

/**
 * updateConnectionStatus().
 */
void Client::updateConnectionStatus() {
    this->stayConnected = !stayConnected;
}

/**
 * connectToServer().
 */
void Client::connectToServer() {
    // Init socket
    this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->clientSocket < 0) {
        throw "Failed to bind socket";
    }
    // Memset the connection details
    memset(&this->connectionDetails, 0, sizeof(this->connectionDetails));
    this->connectionDetails.sin_family = AF_INET;
    this->connectionDetails.sin_addr.s_addr = inet_addr(serverIP.c_str());
    this->connectionDetails.sin_port = htons(serverPort);

    // connect to a server
    if (connect(this->clientSocket,
                (struct sockaddr *) &this->connectionDetails,
                sizeof(this->connectionDetails)) < 0) {
        throw ">> Failure: opening socket.";

    }
}

/**
 * connected().
 */
void Client::connected() {
    // Local Variables
    std::string serverMessage;
    char msg[MAX_MESSAGE_SIZE] = {0};
    char dummy;
    MessageType messageType;
    bool skipWrite = false;

    // garbage collection from main.
    scanf("%c", &dummy);

    // read and print server instructions
    read(clientSocket, msg, MAX_MESSAGE_SIZE);
    cout << msg;

    memset(msg, 0, MAX_MESSAGE_SIZE);   // clear msg

    do {
        if (!skipWrite) {
            // write
            writeMessageToServer();
        }

        // read server traffic
        readMessageFromServer(&messageType, &skipWrite);

    } while (stayConnected);
}

/**
 * writeMessateToServer().
 */
void Client::writeMessageToServer() {
    // Local Variables
    char msg[MAX_MESSAGE_SIZE] = {0};
    std::string str;

    // write command to socket
    cout << "Enter a command\n";
    fgets(msg, MAX_MESSAGE_SIZE, stdin);

    // copy message to string
    str = clearAndCheckString(msg, MAX_MESSAGE_SIZE);

    // write message
    write(clientSocket, str.c_str(), str.length() + 1);
    memset(msg, 0, MAX_MESSAGE_SIZE); // clear msg
}

/**
 * readTrafficUntilCommandResult().
 */
void Client::readMessageFromServer(MessageType *messageType, bool *skipWrite) {
    // Local Variables
    char msg[MAX_MESSAGE_SIZE] = {0};

    if(read(clientSocket, msg, MAX_MESSAGE_SIZE) < 0) {
        cout << "Server shut down for unknown reason...";
        exit (-1);
    }

    *messageType = (MessageType) (*(msg + MESSAGE_TYPE_OFFSET) - '0');

    char *dataOffset = msg + MESSAGE_DATA_OFFSET;

    // notification
    if (*messageType == NOTIFICATION) {
        *skipWrite = readNotification(dataOffset);
        return;
    }

    // command result
    if (*messageType == COMMAND_RESULT) {
        *skipWrite = readCommandResult(dataOffset);
        return;
    }
}

/**
 * readCommandResult().
 */
bool Client::readCommandResult(char *msgPtr) {
    // Local Variables
    bool skipRead = false;
    bool keepCom = (bool) (*(msgPtr + COMMAND_RESULT_KEEPCOM_OFFSET) - '0');
    Command cmd = (Command) (*(msgPtr + COMMAND_RESULT_COMMAND_OFFSET) - '0');

    if (!keepCom)
        updateConnectionStatus();

    if (cmd == CLOSE || cmd == PLAY || cmd == JOIN || cmd == START) {
        // explanation:
        //  START -- wait for opponent to join
        //  PLAY -- need to read update message
        //  CLOSE -- doesn't matter really -> will break loop
        //  JOIN -- wait for other player to make a move

        skipRead = true;
    }
    // print "game started" message
    msgPtr += COMMAND_RESULT_DATA_OFFSET;
    std::cout << msgPtr;

    return skipRead;
}

/**
 * readNotification();
 */
bool Client::readNotification(char *msgPtr) {
    // Local Variables
    bool skipWrite = false;
    NotificationType notificationType = (NotificationType) (*(msgPtr + NOTIFICATION_TYPE_OFFSET) - '0');

    if (notificationType == GAME_OVER)
        updateConnectionStatus();

    if(notificationType == PLAYER_MOVE)
        skipWrite = true;

    // joined game -- print message
    msgPtr += NOTIFICATION_DATA_OFFSET;
    std::cout << msgPtr;

    return skipWrite;
}

/*// Local Variables
    char msg[MAX_MESSAGE_SIZE] = {0};
    char *msgPtr = msg;
    MessageType messageType;

    // read a message from server
    if (read(clientSocket, msg, MAX_MESSAGE_SIZE) < 0) {
        cout << "Server was closed for an unknown reason";
        exit(-1);
    }

    messageType = (MessageType) (*(msgPtr + MESSAGE_TYPE_OFFSET) - '0');

    // notification
    if(messageType == NOTIFICATION) {
        msgPtr += MESSAGE_DATA_OFFSET;
        NotificationType notificationType = (NotificationType) (*(msgPtr + NOTIFICATION_TYPE_OFFSET) - '0');

        if(notificationType == GAME_OVER)
            updateConnectionStatus();

        // get played notification -> read play cmd -> wait for other player to play -> return (ur turn)
        if(notificationType == PLAYER_MOVE) {
            // joined game -- print message
            msgPtr += COMMAND_RESULT_DATA_OFFSET;
            std::cout << msgPtr;
            return;
        }

        // started notif -> print -> print joined cmd -> return
        if(notificationType == GAME_STARTED) {
            // print "game started" message
            msgPtr += COMMAND_RESULT_DATA_OFFSET;
            std::cout << msgPtr;

            memset(msg, 0, MAX_MESSAGE_SIZE);   // clear msg
            msgPtr = msg;

            // wait for the other player to make a move...
            if(read(clientSocket, msg, MAX_MESSAGE_SIZE) < 0) {
                cout << "Server was closed for an unknown reason" << endl;
                exit(-1);
            }

            msgPtr += MESSAGE_DATA_OFFSET;
            msgPtr += COMMAND_RESULT_DATA_OFFSET;

            cout << msgPtr;
            return;
        }

    }

    // command result
    if(messageType == COMMAND_RESULT) {
        msgPtr += MESSAGE_DATA_OFFSET;
        bool keepCom = (bool) (*(msgPtr + COMMAND_RESULT_KEEPCOM_OFFSET) - '0');
        Command cmd = (Command) (*(msgPtr + COMMAND_RESULT_COMMAND_OFFSET) - '0');

        if(!keepCom)
            updateConnectionStatus();

        // print error received
        if(cmd == ERROR || cmd == UNKNOWN_MESSAGE_TYPE || cmd == LIST) {
            // print "game started" message
            msgPtr += COMMAND_RESULT_DATA_OFFSET;
            std::cout << msgPtr;

            return;
        }

        // print created -> wait for other client (read notification)-> return (make a move)
        if(cmd == START) {
            // print "game started" message
            msgPtr += COMMAND_RESULT_DATA_OFFSET;
            std::cout << msgPtr;

            memset(msg, 0, MAX_MESSAGE_SIZE);   // clear msg
            msgPtr = msg;

            // need to wait for another player
            if(read(clientSocket, msg, MAX_MESSAGE_SIZE) < 0) {
                cout << "Server was closed for an unknown reason" << endl;
                exit(-1);
            }

            msgPtr += MESSAGE_DATA_OFFSET;
            msgPtr += COMMAND_RESULT_DATA_OFFSET;

            cout << msgPtr;
            return;
        }

        if(cmd == JOIN) {
            // print "joined game" message
            msgPtr += COMMAND_RESULT_DATA_OFFSET;
            std::cout << msgPtr;

            memset(msg, 0, MAX_MESSAGE_SIZE);   // clear msg
            msgPtr = msg;

            // wait for other player's move
            if(read(clientSocket, msg, MAX_MESSAGE_SIZE) < 0) {
                cout << "Server was closed for an unknown reason" << endl;
                exit(-1);
            }

            msgPtr += MESSAGE_DATA_OFFSET;
            msgPtr += COMMAND_RESULT_DATA_OFFSET;

            cout << msgPtr;
            return;
        }

        if(cmd == PLAY) {
            // print "joined game" message
            msgPtr += COMMAND_RESULT_DATA_OFFSET;
            std::cout << msgPtr;

            memset(msg, 0, MAX_MESSAGE_SIZE);   // clear msg
            msgPtr = msg;

            // wait for other player's move
            if(read(clientSocket, msg, MAX_MESSAGE_SIZE) < 0) {
                cout << "Server was closed for an unknown reason" << endl;
                exit(-1);
            }

            msgPtr += MESSAGE_DATA_OFFSET;
            msgPtr += COMMAND_RESULT_DATA_OFFSET;

            cout << msgPtr;
            return;
        }
    }*/