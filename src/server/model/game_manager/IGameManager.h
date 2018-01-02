//
// Created by alonv on 12/23/2017.
//

#ifndef AP1_EX3_IGAMEMANAGER_H
#define AP1_EX3_IGAMEMANAGER_H

#include "IGameContainer.h"
#include "../../controller/IGameEventHandler.h"

class IGameManager : public IGameContainer, public IGameEventHandler {
public:
    virtual ~IGameManager() {}
};

#endif //AP1_EX3_IGAMEMANAGER_H
