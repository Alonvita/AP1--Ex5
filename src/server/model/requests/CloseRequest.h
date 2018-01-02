//
// Created by alonv on 12/23/2017.
//

#ifndef AP1_EX3_CLOSEREQUEST_H
#define AP1_EX3_CLOSEREQUEST_H

#include <string>
#include "../../IClient.h"
#include "IRequest.h"

class CloseRequest : public IRequest {
public:
    CloseRequest(IClient* client, std::string name): client(client), name(name) {};

    IClient*    getClient();
    std::string getName();

private:
    IClient*    client;
    std::string name;
};


#endif //AP1_EX3_CLOSEREQUEST_H
