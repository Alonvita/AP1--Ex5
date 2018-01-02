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
    char dummy;
    char msg[MAX_MESSAGE_SIZE] = {0};

    // read ad print server instructions
    read(clientSocket, msg, MAX_MESSAGE_SIZE);
    cout << msg;

    // scan the \n from main menu
    scanf("%c", &dummy);

    do {
        // write
        writeMessageToServer();

        // read server traffic
        serverMessage = readTrafficUntilCommandResult();

        // print message
        cout << serverMessage << endl;

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
 *
 * @return the command result as a string
 */
std::string Client::readTrafficUntilCommandResult() {
    // Local Variables
    char msg[MAX_MESSAGE_SIZE] = {0};
    std::string serverMessage;
    MessageType messageType = UNKNOWN_MESSAGE_TYPE;

    do {
        // read a message from server
        if (read(clientSocket, msg, MAX_MESSAGE_SIZE) < 0) {
            cout << "Server was closed for an unknown reason";
            exit(-1);
        }

        serverMessage = serializeServerMessage(msg, &messageType);
    } while (messageType != COMMAND_RESULT);

    // return the message serialized
    return serverMessage;
}

/**
 * serializeServerMessage(char *msg, MessageType *messageType).
 * @param msg *char -- an array of chars, assumes initialized.
 * @param messageType *MessageType -- a reference to MessageType type to update.
 *
 * @return the serialized message as a std::string
 */
std::string Client::serializeServerMessage(char msg[MAX_MESSAGE_SIZE], MessageType *messageType) {
    // check message type
    if (*(msg + MESSAGE_TYPE_OFFSET) - '0' == UNKNOWN_MESSAGE_TYPE) {
        *messageType = UNKNOWN_MESSAGE_TYPE;
    }

    if (*(msg + MESSAGE_TYPE_OFFSET) - '0' == NOTIFICATION) {
        *messageType = NOTIFICATION;
        return serializeNotification(msg + MESSAGE_DATA_OFFSET);
    }

    if (*(msg + MESSAGE_TYPE_OFFSET) - '0' == COMMAND_RESULT) {
        *messageType = COMMAND_RESULT;
        return serializeCommandResult(msg + MESSAGE_DATA_OFFSET);
    }
}

/**
 * notificationReceived(char msg[MAX_MESSAGE_SIZE]).
 * @param msg *char -- an array of chars, assumes initalized.
 *
 * @return the serialized Notification as a std::string
 */
std::string Client::serializeNotification(char *msg) {
    // Local Variables
    NotificationType notificationType = (NotificationType) (*(msg + NOTIFICATION_TYPE_OFFSET) - '0');

    if (notificationType == GAME_OVER)
        updateConnectionStatus();

    // point msg to the beginning of the Notifications data
    msg = msg + NOTIFICATION_DATA_OFFSET;

    return std::string(msg);
}

/**
 * commandResultReceived(char msg[MAX_MESSAGE_SIZE]).
 * @param msg *char -- an array of chars, assumes initalized.
 * @ returns the serialized CommandResult as a std::string
 */
std::string Client::serializeCommandResult(char *msg) {
    bool success = (bool) (*(msg + COMMAND_RESULT_SUCCESS_OFFSET) - '0');
    Command command = (Command) (*(msg + COMMAND_RESULT_COMMAND_OFFSET) - '0');

    if (!((bool) ((msg + COMMAND_RESULT_KEEPCOM_OFFSET) - '0'))) {
        updateConnectionStatus();
    }

    // point msg to the beginning of the CommandResult data
    msg = msg + COMMAND_RESULT_DATA_OFFSET;

    return std::string(msg);
}