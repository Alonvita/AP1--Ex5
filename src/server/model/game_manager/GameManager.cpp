//
// Created by alonv on 12/23/2017.
//

#include "GameManager.h"

/**
 * GameManager(IGameContainer container, IGameEventHandler handler).
 *
 * @param container IGameContainer -- a game container.
 * @param handler IGameEventHandler --
 */
GameManager::GameManager(IGameContainer *container, IGameEventHandler *handler) {
    this->container = container;
    this->handler = handler;
}

/**
 * attachHandlers(ReversiGame *game).
 * @param game ReversiGame -- a reference to a game to add this handler to, as a handler.
 */
void GameManager::attachHandlers(ReversiGame *game) {
    game->addHandler(this);
}

/**
 * detachHandelers(ReversiGame *game).
 *
 * @param game ReversiGame -- a reference to the game to detach the handlers from.
 */
void GameManager::detachHandlers(ReversiGame *game) {
    game->removeHandler();
}

/**
 * GameManager::getHandler().
 *
 * @return the handler of this GameManager
 */
IGameEventHandler* GameManager::getHandler() {
    return this->handler;
}

/**
 * handleGameStarted(ReversiGame* game).
 *
 * @param game ReversiGame -- a reference to the game that has started.
 */
void GameManager::handleGameStarted(ReversiGame* game) {
    this->handler->handleGameStarted(game);
}

/**
 * handleGameOver(ReversiGame* game, GameOverEventArgs args).
 *
 * @param game ReversiGame -- a referense to the game that was has just finished.
 * @param args GameOverEventArgs -- the arguments of this game
 */
void GameManager::handleGameOver(ReversiGame* game, GameOverEventArgs *args) {
    this->handler->handleGameOver(game, args);
}

/**
 * handlePlayerMoved(ReversiGame* game, IClient player, CellIndex cI).
 *
 * @param game ReversiGame -- a reference to the move that the game was made on.
 * @param player IClient -- FD of the client that moves.
 * @param cI CellIndex -- the move made.
 */
void GameManager::handlePlayerMoved(ReversiGame* game, IClient* player, CellIndex cI) {
    this->handler->handlePlayerMoved(game, player, cI);
}

/**
 * handlePlayerMoved(ReversiGame* game, IClient player, CellIndex cI).
 *
 * @param game ReversiGame* -- a reference to the game the illegal move was
 *                              made on
 * @param player IClient* -- a client type.
 */
void GameManager::handleIllegalMove(ReversiGame *game, IClient *player) {
    this->handler->handleIllegalMove(game, player);
}

/**
 * handleException (std::string exception, IClient *player).
 *
 * @param exception std::string -- a string representing the problem
 * @param player IClient -- a client type to notify.
 */
void GameManager::handleException (std::string exception, IClient *player) {
    this->handler->handleException(exception, player);
}

/**
 * addGame(Game game).
 * @param game Game -- a game to add to container.
 */
void GameManager::addGame(ReversiGame *game) {
    if (container->containsGame(game))
        std::runtime_error("Game already exists.");

    attachHandlers(game);
    container->addGame(game);
}

/**
 * containsGame(IClient* client).
 *
 * @param client IClient* -- a client type.
 *
 * @return true if this GameManager contains thie client, or false otherwise.
 */
bool GameManager::containsGame(IClient* client) {
    return(container->containsGame(client));
}

/**
 * removeGame(Game game).
 * @param game Game -- a game to remove.
 */
void GameManager::removeGame(ReversiGame *game) {
    container->removeGame(game);
    detachHandlers(game);
}

/**
 *containsGame(string name).
 *
 * @param name string -- a string representing the game name.
 * @return true if the container contains the game, or false otherwise.
 */
bool GameManager::containsGame(string name) {
    return container->containsGame(name);
}

/**
 * containsGame(Game game).
 *
 * @param game Game -- a ptr of a reversi game.
 * @return true if the container contains the game, or false otherwise.
 */
bool GameManager::containsGame(ReversiGame *game) {
    return container->containsGame(game);
}

/**
 * getGame(IClient client).
 *
 * @param client IClient -- a client.
 * @return the game that this client is playing in.
 */
ReversiGame *GameManager::getGame(IClient* client) {
    return container->getGame(client);
}

/**
 * getGame(string name).
 *
 * @param name string -- a game name.
 * @return the game represented by this string.
 */
ReversiGame *GameManager::getGame(string name) {
    return container->getGame(name);
}

/**
 * GameManager::listGames().
 * @return a vector of all joinable games
 */
std::vector<std::string> GameManager::listGames() {
    return container->listGames();
}