//
// Created by alonv on 12/23/2017.
//

#ifndef AP1_EX3_REVERSIGAMEGENERATOR_H
#define AP1_EX3_REVERSIGAMEGENERATOR_H

#include <string>
#include "IGameGenerator.h"
#include "../../../../game/game_flow/Reversi.h"
#include "../ReversiGame.h"

class ReversiGameGenerator : public IGameGenerator {
public:
    void *generateGame(std::string name);
};

#endif //AP1_EX3_REVERSIGAMEGENERATOR_H
