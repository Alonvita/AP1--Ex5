//
// Created by alonv on 12/23/2017.
//

#ifndef AP1_EX3_GAMEMANAGER_H
#define AP1_EX3_GAMEMANAGER_H

#include "IGameManager.h"

class GameManager : public IGameManager {
public:
    GameManager(IGameContainer *container, IGameEventHandler *handler);
    ~GameManager() {}

    void handleGameStarted  (ReversiGame *game);
    void handleGameOver     (ReversiGame *game, GameOverEventArgs *args);
    void handlePlayerMoved  (ReversiGame *game, IClient* player, CellIndex cI);
    void handleIllegalMove  (ReversiGame *game, IClient *player);
    void handleException    (std::string exception, IClient *player);

    // handling
    void attachHandlers     (ReversiGame *game);
    void detachHandlers     (ReversiGame *game);

    // getters & setters
    IGameEventHandler*      getHandler();

    void addGame        (ReversiGame *game);
    void removeGame     (ReversiGame *game);
    bool containsGame   (IClient* client);
    bool containsGame   (string name);
    bool containsGame   (ReversiGame *game);

    // getters & setters
    ReversiGame*                 getGame(IClient* client)    override;
    ReversiGame*                 getGame(string name)       override;
    std::vector<std::string>     listGames();

private:
    IGameContainer*     container;
    IGameEventHandler*  handler;
};

#endif //AP1_EX3_GAMEMANAGER_H