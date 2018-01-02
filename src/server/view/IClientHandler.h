//
// Created by alonv on 12/29/2017.
//

#ifndef AP1_EX3_ICLIENTHANDLER_H
#define AP1_EX3_ICLIENTHANDLER_H

#include "ServerClient.h"

class IClientHandler {
public:
    ~IClientHandler(){}

    virtual void handleClient(IClient* client) = 0;
};

#endif //AP1_EX3_ICLIENTHANDLER_H
