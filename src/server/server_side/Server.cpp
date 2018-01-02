/**
 * Project:    Ex5.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * Class Server.
 *
 * This class will handle everything on the server side.
 */


#include "Server.h"

#include "../../easy_logging/easylogging++.h"

//---------- INITIALIZATION ----------
/**
 * Server(int port).
 *
 * @param int port -- server's port.
 */
Server::Server(int port) : port(port) {
    threadPool = new ThreadPool(0);
    serverSocket = -1;
}

//---------- DESTRUCTION ----------

/**
 * ~Server().
 */
Server::~Server() {
    close(this->serverSocket);

    delete threadPool;
}

//----------PUBLIC FUNCTIONS----------
/**
 * start().
 */
void Server::start() {
    // Create a socket point
    initSocket();
    // add a ClientHandler (also implements Task)
    ClientHandler *handler = new ClientHandler();

    while (true) {
        try {
            // accept a new client_side connection
            IClient *c = new ServerClient(clientConnected());

            if (c->getSocket() < 0) {
                throw ("Client socket corrupted");
            } else {
                // got client
                cout << "Got a new client connection: " + intToString(c->getSocket());

                // print client options for this server
                writeClientOptions(c->getSocket());

                // add a thread
                threadPool->addWorkerThreads(1);

                handler->handleClient(c);

                //LINFO << "Creating a new Thread Task for: " << c->getSocket();
                threadPool->addTask(handler->getClientTask());

                c = nullptr;
            }
        } catch (exception& e) {
            break;
        }
    }
}

/**
 * initSocket().
 */
void Server::initSocket() {
    // Server initialization begins
    initializingSocketAnnouncement();

    // Socket TCP
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }

    // Initialize serverAddress
    struct sockaddr_in serverAddress;

    bzero((void *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    // Bind socket to port
    if (bind(serverSocket,
             (struct sockaddr *) &serverAddress,
             sizeof(serverAddress)) == -1) {
        throw "Error binding to socket";
    }

    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);

    serverListeningAnnouncement(this->port);
}

/**
 * stop().
 */
void Server::stop() {
    close(this->serverSocket);
}

/**
 * clientConnected().
 *
 * @return clientSocket fd if client connected succesfuly, or false otherwise.
 */
int Server::clientConnected() {
    int fd = accept(serverSocket, 0, 0);
    // connection not established
    if (fd == -1)
        throw "Error while accepting ServerClient";
    LDEBUG << "Accepted: " << fd;
    return fd;
}

/**
 * writeClientOptions();
 */
void Server::writeClientOptions(int clientSocket) {
    std::string optionsMsg;

    optionsMsg = "Welcome to the server, here are your options: \n";
    optionsMsg += "----- MAIN MENU -----\n";
    optionsMsg += "write: \'start\' \'[game_name]\' to start a new game\n";
    optionsMsg += "write: \'list\' to get the list of available games\n";
    optionsMsg += "write: \'join\' \'[game_name]\' to join a game\n";
    optionsMsg += "----- IN-GAME -----\n";
    optionsMsg += "once in a game, you can write the following messages:\n";
    optionsMsg += "\'play\' \'X,Y\' to make a move on the game board\n";
    optionsMsg += "write \'close\' \'[game_name]\' to close "
                        "the game you are participating in";
    optionsMsg += "\n\n";

    write(clientSocket, optionsMsg.c_str(), optionsMsg.size());
}