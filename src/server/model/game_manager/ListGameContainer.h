//
// Created by alonv on 12/23/2017.
//

#ifndef AP1_EX3_LISTGAMECONTAINER_H
#define AP1_EX3_LISTGAMECONTAINER_H

#include "IGameContainer.h"
#include "../../../game/game_flow/Reversi.h"
#include "../reversi_game/ReversiGame.h"

class ListGameContainer : public IGameContainer {
public:
    ListGameContainer() = default;

    // container
    bool containsGame(std::string name)     override;
    bool containsGame(IClient* client)       override;
    bool containsGame(ReversiGame* game)    override;

    void addGame(ReversiGame *game)     override;
    void removeGame(ReversiGame *game)  override;

    // getters & setters
    ReversiGame*                getGame(std::string name);
    ReversiGame*                getGame(IClient* client);
    std::vector<std::string>    listGames();


private:
    std::vector<ReversiGame *> games;
};

#endif //AP1_EX3_LISTGAMECONTAINER_H