//
// Created by alonv on 12/23/2017.
//

#ifndef AP1_EX3_IGAMEEVENTHANDLER_H
#define AP1_EX3_IGAMEEVENTHANDLER_H

#include <string>
#include "../model/reversi_game/ReversiGame.h"
#include "../model/reversi_game/ReversiGameEvent.h"

class ReversiGame;
class GameOverEventArgs;

class IGameEventHandler {
public:
    ~IGameEventHandler() {}

    virtual void handleGameStarted  (ReversiGame* game) = 0;
    virtual void handleIllegalMove  (ReversiGame* game, IClient* player) = 0;
    virtual void handleGameOver     (ReversiGame* game, GameOverEventArgs* args) = 0;
    virtual void handlePlayerMoved  (ReversiGame* game, IClient* player, CellIndex cI) = 0;
    virtual void handleException    (std::string exception, IClient *player) = 0;
};

#endif //AP1_EX3_IGAMEEVENTHANDLER_H
