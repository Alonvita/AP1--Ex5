//
// Created by alonv on 12/23/2017.
//

#ifndef AP1_EX3_IGAMEGENERATOR_H
#define AP1_EX3_IGAMEGENERATOR_H

#include "../../../controller/IGameEventHandler.h"

class IGameGenerator {
public:
    virtual void *generateGame(std::string name) = 0;
};

#endif //AP1_EX3_IGAMEGENERATOR_H
