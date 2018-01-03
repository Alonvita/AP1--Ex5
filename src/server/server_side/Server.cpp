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

    // add a thread
    threadPool->addWorkerThreads(1);

    // add server Task as a main thread
    ServerTask *serverTask = new ServerTask(threadPool, serverSocket);
    threadPool->addTask(serverTask);
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