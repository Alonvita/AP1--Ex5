//
// Created by alonv on 12/23/2017.
//

#ifndef AP1_EX3_REVERSIGAME_H
#define AP1_EX3_REVERSIGAME_H

#include <string>
#include <vector>
#include <stdexcept>
#include "ReversiGamePlayer.h"
#include "../../../game/board/Cell.h"
#include "../../../game/game_flow/Reversi.h"
#include "../../controller/IGameEventHandler.h"

#define GAME_STARTED_EVENT(game) this->controllerListener->handleGameStarted(game)
#define PLAYER_ILLEGAL_MOVE(game, player) this->controllerListener->handleIllegalMove(game, player)
#define GAME_OVER_EVENT(game, gameOverArgs) this->controllerListener->handleGameOver(game, gameOverArgs)
#define PLAYER_MOVED_EVENT(game, player, cI) this->controllerListener->handlePlayerMoved(game, player, cI)
#define EXCEPTION(exception, player) this->controllerListener->handleException(exception, player)

class IGameEventHandler;

class ReversiGame {

public:
    ReversiGame(std::string name);
    ~ReversiGame();

    // container control
    void addPlayer       (IClient* client);
    void closeGame       (IClient* client);
    bool containsClient  (IClient* client);
    std::vector<ReversiGamePlayer*>* getAllClients();

    // getters & setters -- game status
    bool getStarted();
    bool getFinished();
    std::vector<CellIndex> getAvailableMoves();

    // getters & setters -- game info
    Board*      getBoard();
    std::string getName();
    ReversiGamePlayer *getPlayerByClient(IClient* client);

    // game control
    void start      ();
    void close      ();
    bool playMove   (IClient* client, CellIndex cI);

    // listeners control
    void addHandler(IGameEventHandler* eventHandler);
    void removeHandler();
private:
    // variables
    TurnsManager*   turnsManager;
    Board*          gameBoard;
    std::string     name;
    std::vector<ReversiGamePlayer *> players;

    // listeners
    IGameEventHandler* controllerListener;

    // state
    bool started;
    bool finished;

    // private functions
    void finish     (ReversiGamePlayer* winner);
    bool legalMove  (CellIndex cI);
    void checkWin   (ReversiGamePlayer* player);
};

#endif //AP1_EX3_REVERSIGAME_H