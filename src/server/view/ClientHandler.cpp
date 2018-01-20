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
 * ~ClientHandler().
 */
ClientHandler::~ClientHandler() {
    delete this->controller;
    delete this->client;
}

/**
 * HandleClient(Client client).
 *
 * @param client Client -- a client.
 */
void ClientHandler::handleClient(IClient* client) {
    this->client = client;
    createClientTask(client);
}

/**
 * createClientTask(ServerClient* client).
 *
 * @param client ServerClient* - a reference to the client we want to create
 *                                  the task for
 */
void ClientHandler::createClientTask(IClient* client) {
    task = new ClientTask(((ServerClient*) client), controller);
}

/**
 * getClientTask().
 * @return the last client task created by the handler.
 */
ClientTask* ClientHandler::getClientTask() {
    return task;
}

/**
 * notifyClient(IClient* client, Notification notification).
 *
 * @param client IClient -- a client type.
 * @param notification Notification -- a message notification.
 */
void ClientHandler::notifyClient(IClient* client, Notification* notification) {
    try {
        ((ServerClient*) client)->sendNotification(notification);
    } catch (exception& e) {
        std::string socket = intToString(client->getSocket());

        throw ("Could not reach %s. Closing the connection." + socket);
    }
}