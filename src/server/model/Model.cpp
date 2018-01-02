//
// Created by alonv on 12/23/2017.
//


#include "Model.h"
#include "../../easy_logging/easylogging++.h"

Model::Model(IGameEventHandler* handler) {
    this->gameManager =         new GameManager(new ListGameContainer(), handler);
    this->gameGenerator =       new ReversiGameGenerator;
    this->reversiGameManager =  new ReversiGameManager();
}

/**
 * createGame(StartRequest request, IGameEventHandler* gameEventHandler).
 *
 * @param request StartRequest -- a request containing 'start' and a game name.
 * @param gameEventHandler IGameEventHandler -- a reference to the handler this game was created from.
 */
void Model::createGame(StartRequest* request) {
    // initialzie a new game
    ReversiGame* game =
            ((ReversiGameManager*)reversiGameManager)->
                    generateReversiGame(request);

    gameManager->addGame(game);             // add game to manager
    game->addPlayer(request->getClient());  // add client to the game
    // add handler to the game
    game->addHandler(
            ((GameManager*)gameManager)->getHandler());

    LINFO << "Game was created: " << game->getName()
          << "\tPlayer: " << request->getClient()->getSocket()
          << " was added to the game";
}

/**
 * listGames().
 *
 * @return the list of available games.
 */
std::vector<std::string> Model::listGames() {
    // Local variables
    return this->gameManager->listGames();
}

/**
 * gameExists(std::string str).
 *
 * @param str std::string -- a game name.
 * @return true if the gameManager contains a game under this name, or false
 *          otherwise
 */
bool Model::gameExists(std::string str) {
    return this->gameManager->containsGame(str);
}

/**
 * isInGame(IClient c).
 *
 * @param c IClient -- a client identifier
 * @return true if the client is already in a game, false otherwise
 */
bool Model::isInGame(IClient* c) {
    return gameManager->containsGame(c);
}

/**
 * joinGame(JoinRequest request).
 *
 * @param request JoinRequest -- a request contains 'join' and the game's name
 */
void Model::joinGame(JoinRequest* request) {
    // get a reference to the game requested
    ReversiGame* gameToJoin = gameManager->getGame(request->getName());

    // add player to game
    gameToJoin->addPlayer(request->getClient());
}

/**
 * playMove(PlayRequest request).
 *
 * @param request PlayRequest -- a request containing a CellIndex
 * @return true if the move was succesfully made, or false otherwise
 */
void Model::playMove(PlayRequest* request) {
    ReversiGame* game = gameManager->getGame(request->getClient());

    game->playMove(request->getClient(), request->getMove());
}

/**
 * closeGame(CloseRequest request).
 * @param request CloseRequest -- a request containing client identifier and a game name.
 */
void Model::closeGame(CloseRequest* request) {
    ReversiGame* game = gameManager->getGame(request->getClient());

    // remove player from game
    game->closeGame(request->getClient());

    gameManager->removeGame(game);
}