//
// Created by alonv on 12/23/2017.
//

#ifndef AP1_EX3_REVERSIGAMEMANAGER_H
#define AP1_EX3_REVERSIGAMEMANAGER_H


#include "IReversiGameManager.h"
#include "../reversi_game/generator/IGameGenerator.h"
#include "../reversi_game/generator/ReversiGameGenerator.h"

class ReversiGameManager : public IReversiGameManager {
public:
    ReversiGameManager();
    ~ReversiGameManager();

    ReversiGame *generateReversiGame(StartRequest* request);

private:
    IGameGenerator* gameGen;
    std::vector<ReversiGame*> reversiGames;
};


#endif //AP1_EX3_REVERSIGAMEMANAGER_H
