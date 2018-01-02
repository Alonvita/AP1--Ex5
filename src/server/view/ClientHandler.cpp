//
// Created by alonv on 12/29/2017.
//

#include "ClientHandler.h"
#include "../../easy_logging/easylogging++.h"

/**
 * ClientHandler(Client* client).
 */
ClientHandler::ClientHandler() {
    this->controller = new Controller(this);

}

/**
 * HandleClient(Client client).
 *
 * @param client Client -- a client.
 */
void ClientHandler::handleClient(IClient* client) {
    LINFO <<"Creating a client task for " << client->getSocket();
    createClientTask(client);
    LINFO <<"DONE Creating a client task for " << client->getSocket();
}

/**
 * createClientTask(ServerClient* client).
 *
 * @param client ServerClient* - a reference to the client we want to create
 *                                  the task for
 */
void ClientHandler::createClientTask(IClient* client) {
    task = new ClientTask(((ServerClient*) client), controller);
    LINFO <<"Client task: " << task;
}

/**
 * getClientTask().
 * @return the last client task created by the handler.
 */
ClientTask* ClientHandler::getClientTask() {
    LINFO <<"Inside \'getClientTask\', initializing temp";
    ClientTask* temp = task;
    task = nullptr;

    LINFO << "Inside \'getClientTask\' sending temp: " << temp;
    return temp;
}

/**
 * notifyClient(IClient* client, Notification notification).
 *
 * @param client IClient -- a client type.
 * @param notification Notification -- a message notification.
 */
void ClientHandler::notifyClient(IClient* client, Notification* notification) {
    try {
        LINFO <<"Sending notification to: " << client->getSocket();
        ((ServerClient*) client)->sendNotification(notification);
        LINFO <<"Sending notification to: " << client->getSocket() << " done";
    } catch (exception& e) {
        std::string socket = intToString(client->getSocket());

        throw ("Could not reach %s. Closing the connection." + socket);
    }
}