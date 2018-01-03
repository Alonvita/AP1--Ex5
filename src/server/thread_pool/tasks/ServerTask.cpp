//
// Created by alon_vita on 1/3/18.
//

#include <sys/socket.h>
#include "ServerTask.h"
#include "../../view/ClientHandler.h"
#include "../../../easy_logging/easylogging++.h"

/**
 * ServerTask(ThreadPool *threadPool, int serverSocket).
 * @param threadPool ThreadPool* -- a referense to the server's threadpool
 * @param serverSocket int -- the server socket.
 */
ServerTask::ServerTask(ThreadPool *threadPool, int serverSocket) {
    this->threadPool = threadPool;
    this->serverSocket = serverSocket;
}

/**
 * run().
 */
void ServerTask::run() {
    // add a ClientHandler (also implements Task)
    ClientHandler *handler = new ClientHandler();

    while (true) {
        try {
            // accept a new client_side connection
            IClient *c = new ServerClient(clientConnected(this->serverSocket));

            if (c->getSocket() < 0) {
                throw ("Client socket corrupted");
            } else {
                // got client
                LINFO << "Got a new client connection: " + intToString(c->getSocket());

                // print client options for this server
                writeClientOptions(c->getSocket());

                // add a thread
                threadPool->addWorkerThreads(1);

                handler->handleClient(c);

                threadPool->addTask(handler->getClientTask());

                c = nullptr;
            }
        } catch (exception& e) {
            break;
        }
    }
}


/**
 * clientConnected().
 *
 * @param serverSocket int -- the server socket.
 * @return clientSocket fd if client connected succesfuly, or false otherwise.
 */
int ServerTask::clientConnected(int serverSocket) {
    // Local Variables
    int fd = accept(serverSocket, 0, 0);

    // connection not established
    if (fd == -1)
        throw "Error while accepting ServerClient";

    return fd;
}

/**
 * writeClientOptions();
 */
void ServerTask::writeClientOptions(int clientSocket) {
    std::string optionsMsg;

    optionsMsg = "Welcome to the server, here are your options:\n\n";
    optionsMsg += " -------------------- MAIN MENU -------------------\n";
    optionsMsg += "| write: \'start\' \'[game_name]\' to start a new game |\n";
    optionsMsg += "| write: \'list\' to get the list of available games |\n";
    optionsMsg += "| write: \'join\' \'[game_name]\' to join a game       |\n";
    optionsMsg += " --------------------------------------------------\n";
    optionsMsg += " -------------------------------- IN-GAME --------------------------------\n";
    optionsMsg += "| once in a game, you can write the following messages: \t\t\t\t  |\n";
    optionsMsg += "| write: \'play\' \'X,Y\' to make a move on the game board \t\t\t\t\t  |\n";
    optionsMsg += "| write: \'close\' \'[game_name]\' to close "
            "the game you are participating in |\n";
    optionsMsg += " -------------------------------------------------------------------------\n";
    optionsMsg += "\n\n";

    write(clientSocket, optionsMsg.c_str(), optionsMsg.size());
}