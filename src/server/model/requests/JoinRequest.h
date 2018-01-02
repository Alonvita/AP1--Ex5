//
// Created by alonv on 12/23/2017.
//

#ifndef AP1_EX3_JOINREQUEST_H
#define AP1_EX3_JOINREQUEST_H

#include <string>
#include "IRequest.h"
#include "../../IClient.h"

class JoinRequest : public IRequest {
public:
    JoinRequest(IClient* client, std::string name): client(client), name(name) {};

    IClient*    getClient();
    std::string getName();

private:
    IClient*    client;
    std::string name;
};

#endif //AP1_EX3_JOINREQUEST_H
