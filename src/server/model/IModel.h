//
// Created by alonv on 12/23/2017.
//

#ifndef AP1_EX3_IMODEL_H
#define AP1_EX3_IMODEL_H

#include <string>
#include <vector>

#include "../IClient.h"
#include "requests/PlayRequest.h"
#include "requests/JoinRequest.h"
#include "requests/StartRequest.h"
#include "requests/CloseRequest.h"
#include "../controller/IGameEventHandler.h"

class IModel {
public:
    virtual bool gameExists(std::string str) = 0;
    virtual bool isInGame   (IClient* c) = 0;
    virtual void closeGame  (CloseRequest* request)     = 0;
    virtual void joinGame   (JoinRequest* request)      = 0;
    virtual void createGame (StartRequest* request)     = 0;
    virtual void playMove   (PlayRequest* request)      = 0;
    virtual std::vector<std::string> listGames()        = 0;
};

#endif //AP1_EX3_IMODEL_H
