//
// Created by alonv on 12/23/2017.
//

#include "ReversiGameManager.h"

/**
 * ReversiGameManager().
 */
ReversiGameManager::ReversiGameManager() {
    gameGen = new ReversiGameGenerator; // load with a factory
}

/**
 * ~ReversiGameManager();
 */
ReversiGameManager::~ReversiGameManager() {
    delete this->gameGen;
}

/**
 * generateReversiGame(IGameEventHandler *controller, StartRequest request).
 *
 * @param request StartRequest -- a request containing a 'start' string and and name.
 *
 * @return
 */
ReversiGame *ReversiGameManager::generateReversiGame(StartRequest* request) {
    // generate a new game
    ReversiGame *rG = (ReversiGame *) gameGen->generateGame(request->getName());

    // insert game to games map
    reversiGames.push_back(rG);

    // return a ptr to the game created
    return rG;
}