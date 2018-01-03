//
// Created by alon on 01/01/18.
//

#include "ClientTask.h"
#include "../../../easy_logging/easylogging++.h"

/**
 * ClientTask().
 */
ClientTask::~ClientTask() {
    delete this->client;
}

/**
 * run().
 */
void ClientTask::run() {
    try {
        bool keepCom = true;
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