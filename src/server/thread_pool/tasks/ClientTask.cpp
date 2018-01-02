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
            //LINFO << "inside ClientTask::run() for client " << client->getSocket();
            LINFO << "Reading from: " << client->getSocket()<< " inside ClientTask::run()";
            string command = client->readMessage();
            LINFO << "message read from: " << client->getSocket() << " inside ClientTask::run()";

            LINFO << "executing message for: " << client->getSocket() << " inside ClientTask::run()";
            CommandResult* result = controller->executeCommand(command, client);
            LINFO << "DONE executing message for: " << client->getSocket() << " inside ClientTask::run()";

            keepCom = result->getKeepConnection();
            //LINFO << "Sending command result for " << client->getSocket();
            client->sendCommandResult(result);
            //LINFO << "DONE Sending command result for " << client->getSocket();

        } while (keepCom && client->isConnected());
    } catch (exception &e) {
        std::runtime_error("Could not reach %s. closing the connection." +
                           intToString(client->getSocket()));
    }
            //LINFO << "leaving ClientTask::run() for client " << client->getSocket();
}