/**
 * Project:    Ex5.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * Class Client.
 *
 * This class will establish Client-Server connection and send Client
 *  requests to the ClientHandler.
 */

#ifndef AP1_EX3_CLIENT_H
#define AP1_EX3_CLIENT_H

//----------INCLUDING----------

#include <unistd.h>

#include "../IClient.h"
#include "../../shared_data/CommandResult.h"
#include "../../shared_data/Notification.h"
#include "../../shared_data/Message.h"

class ServerClient : public IClient {
public:
    // Initializer
    ServerClient(int clientSocket) :
            clientSocket(clientSocket), connected(true) {};

    // Destruct
    ~ServerClient() {}

    //----------PUBLIC FUNCTIONS----------
    // Getters & Setters
    int getSocket();

    bool isConnected();

    void connectionStatusChange(bool status);

    // Server
    std::string readMessage();

    void writeMessage(Message *msg);

    void sendNotification(Notification *notif);

    void sendCommandResult(CommandResult *commandRes);

    bool equals(ServerClient *other);

private:
    // Server Related
    int clientSocket;

    // Game Related
    bool connected;
};

#endif //AP1_EX3_CLIENT_H
