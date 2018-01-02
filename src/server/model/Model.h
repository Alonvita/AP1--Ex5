//
// Created by alonv on 12/23/2017.
//

#ifndef AP1_EX3_MODEL_H
#define AP1_EX3_MODEL_H


#include "IModel.h"
#include "game_manager/GameManager.h"
#include "game_manager/ListGameContainer.h"
#include "../controller/IGameEventHandler.h"
#include "reversi_game/generator/IGameGenerator.h"
#include "reversi_game_manager/ReversiGameManager.h"
#include "reversi_game_manager/IReversiGameManager.h"
#include "reversi_game/generator/ReversiGameGenerator.h"
#include "../../shared_data/CommandResult.h"

class Model : public IModel {
public:
    explicit Model(IGameEventHandler* handler);

    // games control
    void playMove   (PlayRequest* request);
    void closeGame  (CloseRequest* request);
    void createGame (StartRequest* request);
    void joinGame   (JoinRequest* request);

    // container
    bool gameExists(std::string str);
    bool isInGame   (IClient* c);
    std::vector<std::string> listGames();

private:
    IGameGenerator*         gameGenerator;
    IGameManager*           gameManager;
    IReversiGameManager*    reversiGameManager;
};


#endif //AP1_EX3_MODEL_H
