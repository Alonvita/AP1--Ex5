/**
 * Project:    Ex4.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * Class Client.
 *
 * This class will establish Client-Server connection and send Client
 *  requests to the ClientHandler.
 */

#include "ServerClient.h"
#include "../../easy_logging/easylogging++.h"

/**
 * readMessage().
 *
 * @return the read message as string.
 */
std::string ServerClient::readMessage() {
    LINFO << "Reading from: " << clientSocket;
    if (!connected)
        std::runtime_error("ServerClient is not connected to a server.");
    // Local Variables
    char msg[1024];
    //read
    if (read(clientSocket, msg, 1024) == 0) {
        std::runtime_error("fail reading message from server");
    }

    std::string str(msg);

    LINFO << "Message read: " << str;

    return str;
}

/**
 * writeMessage().
 *
 */
void ServerClient::writeMessage(Message* msg) {
    if(!connected)
        std::runtime_error("ServerClient is not connected to a server.");

    LINFO << "Sending message to client: " << clientSocket;
    // write message to server
    std::string message = msg->toString();
    write(clientSocket, message.c_str(), message.length() + 1);
    LINFO << "done Sending message to client: " << clientSocket;
}

/**
 * sendCommandResult(CommandResult result).
 *
 * @param commandRes CommandResult -- a command result to send.
 */
void ServerClient::sendCommandResult(CommandResult* commandRes) {
    Message* msg = new Message(commandRes->toString(), (MessageType) COMMAND_RESULT);

    writeMessage(msg);
}

/**
 * sendNotification(Notification* notif).
 * @param notif Notification* -- a reference to the notification.
 */
void ServerClient::sendNotification(Notification* notif) {
    Message* msg = new Message(notif->toString(), (MessageType) NOTIFICATION);

    writeMessage(msg);
}

/**
 * getSocket().
 *
 * @return this client's fd
 */
int ServerClient::getSocket() {
    return this->clientSocket;
}

/**
 * isConnected().
 *
 * @return true if client is still connected to the server, or false otherwise.
 */
bool ServerClient::isConnected() {
    return this->connected;
}

/**
 * connectionStatusChange(bool status).
 *
 * @param status bool -- connection status to change to
 */
void ServerClient::connectionStatusChange(bool status) {
    this->connected = status;
}

/**
 * ServerClient::equals(ServerClient* other).
 *
 * @param other ServerClient* -- another server client
 * @return true if this and other are equal in FD or false otherwise
 */
bool ServerClient::equals(ServerClient* other) {
    if(other == nullptr)
        return false;
    return this->clientSocket == other->getSocket();
}