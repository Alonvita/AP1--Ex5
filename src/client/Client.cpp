//
// Created by alonv on 12/30/2017.
//

#include "Client.h"
#include "../easy_logging/easylogging++.h"
#include "../shared_data/Notification.h"
#include "../shared_data/CommandResult.h"

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

    // garbage collection from main.
    scanf("%c", &dummy);

    // read and print server instructions
    read(clientSocket, msg, MAX_MESSAGE_SIZE);
    cout << msg;

    do {
        // write
        writeMessageToServer();

        // read server traffic
        readMessageFromServer();

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
void Client::readMessageFromServer() {
    // Local Variables
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
        if((NotificationType) (*(msgPtr + NOTIFICATION_TYPE_OFFSET) - '0') == GAME_OVER)
            updateConnectionStatus();
        msgPtr += NOTIFICATION_DATA_OFFSET;
    }

    // command result
    if(messageType == COMMAND_RESULT) {
        msgPtr += MESSAGE_DATA_OFFSET;
        bool keepCom = (bool) (*(msgPtr + COMMAND_RESULT_KEEPCOM_OFFSET) - '0');
        Command cmd = (Command) (*(msgPtr + COMMAND_RESULT_COMMAND_OFFSET) - '0');

        if(!keepCom)
            updateConnectionStatus();

        if(cmd == START) {
            msgPtr += COMMAND_RESULT_DATA_OFFSET;
            std::cout << msgPtr;
            memset(msg, 0, MAX_MESSAGE_SIZE);           // clear msg
            msgPtr = msg;

            read(clientSocket, msg, MAX_MESSAGE_SIZE);  // read game started notif
            msgPtr += MESSAGE_DATA_OFFSET;
            msgPtr += NOTIFICATION_DATA_OFFSET;
        }

        cout << std::string(msgPtr);
    }
}