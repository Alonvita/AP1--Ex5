//
// Created by alonv on 12/23/2017.
//

#ifndef AP1_EX3_LISTREQUEST_H
#define AP1_EX3_LISTREQUEST_H


#include <string>
#include "../../IClient.h"
#include "IRequest.h"

class StartRequest : public IRequest {
public:
    StartRequest(IClient* client, std::string name): client(client), name(name) {};

    IClient*    getClient();
    std::string getName();

private:
    IClient*    client;
    std::string name;
};


#endif //AP1_EX3_LISTREQUEST_H
