//
// Created by alon on 01/01/18.
//

#include "ClientTask.h"
#include "../../../easy_logging/easylogging++.h"

/**
 * stop().
 */
void ClientTask::stop() {
    keepCom = false;
    this->client->serverClosed();
}

/**
 * run().
 */
void ClientTask::run() {
    try {
        this->keepCom = true;
        do {
            string command = client->readMessage();
            CommandResult* result = controller->executeCommand(command, client);
            keepCom = result->getKeepConnection();
            client->sendCommandResult(result);

        } while (keepCom && client->isConnected());
    } catch (exception &e) {
        std::runtime_error("Could not reach %s. closing the connection." +
                           intToString(client->getSocket()));
    }
            //LINFO << "leaving ClientTask::run() for client " << client->getSocket();
}