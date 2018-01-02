//
// Created by alonv on 12/23/2017.
//

#ifndef AP1_EX3_IGAMECONTAINER_H
#define AP1_EX3_IGAMECONTAINER_H

#include <string>
#include "../../IClient.h"
#include "../../model/reversi_game/ReversiGame.h"

class IGameContainer {
public:
    ~IGameContainer() {}

    // queries
    virtual bool containsGame(std::string name) = 0;
    virtual bool containsGame(IClient* client)  = 0;
    virtual bool containsGame(ReversiGame *game) = 0;

    // list container's available games
    virtual std::vector<std::string> listGames() = 0;

    // getters
    virtual ReversiGame *getGame(string name) = 0;
    virtual ReversiGame *getGame(IClient* client) = 0;

    // adding & removing games
    virtual void addGame(ReversiGame *game) = 0;
    virtual void removeGame(ReversiGame *game) = 0;
};

#endif //AP1_EX3_IGAMECONTAINER_H