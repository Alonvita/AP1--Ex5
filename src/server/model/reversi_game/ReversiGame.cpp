//
// Created by alonv on 12/23/2017.
//

#include "ReversiGame.h"
#include "../../../easy_logging/easylogging++.h"

/**
 * ReversiGame(ReversiGame* rG, std::string name).
 *
 * @param rG ReversiGame* -- ptr to a Reversi game.
 */
ReversiGame::ReversiGame(std::string name) {
    this->name = name;
    this->gameBoard = new Board();
    this->turnsManager = new TurnsManager(2, gameBoard);
    this->started = false;
    this->finished = false;
}

/**
 * ~ReversiGame().
 */
ReversiGame::~ReversiGame() {
    removeHandler();
    delete this->gameBoard;
}

/**
 * addListener(IGameEventHandler gameEventHandler).
 *
 * @param gameEventHandler IGameEventHandler -- an event handler to listen to this Model.
 */
void ReversiGame::addHandler(IGameEventHandler *gameEventHandler) {
    controllerListener = gameEventHandler;
}

/**
 * removeListener().
 */
void ReversiGame::removeHandler() {
    this->controllerListener = nullptr;
}

/**
 * ReversiGame::getBoard().
 *
 * @return a refference to this board.
 */
Board* ReversiGame::getBoard() {
    return this->gameBoard;
}

/**
 * getName().
 *
 * @return this game name as an std::string.
 */
std::string ReversiGame::getName() {
    return this->name;
}

/**
 * getAvailableMoves().
 *
 * @return the available moves at the moment.
 */
std::vector<CellIndex> ReversiGame::getAvailableMoves() {
    return this->turnsManager->getAvailableMoves();
}

/**
 * getStarted().
 *
 * @return true if game has started, or false otherwise
 */
bool ReversiGame::getStarted() {
    return this->started;
}

/**
 * getFinished().
 *
 * @return true if game had finished, or false otherwise
 */
bool ReversiGame::getFinished() {
    return this->finished;
}

/**
 * getPlayerColorByFD(IClient client).
 *
 * @param client IClient -- a client
 * @return the color of the client for this game.
 */
ReversiGamePlayer* ReversiGame::getPlayerByClient(IClient* client) {

    for(unsigned i = 0; i < players.size(); ++i) {
        if (players[i]->getClient()->getSocket() == client->getSocket()) {
            return &(*players[i]);
        }
    }

    return nullptr;
}

/**
 * ReversiGame::getAllClients().
 *
 * @return a ptr to this game's players list.
 */
std::vector<ReversiGamePlayer*> *ReversiGame::getAllClients() {
    return &(this->players);
}

/**
 * start().
 */
void ReversiGame::start() {
    if (started)
        return;

    started = true;
    GAME_STARTED_EVENT(this);
}



/**
 * close().
 */
void ReversiGame::close() {
    if(!started || finished)
        return;

    finished = true;
    GAME_OVER_EVENT(this, new GameOverEventArgs());
}

/**
 * finish(ReversiGamePlayer winner).
 *
 * @param winner ReversiGamePlayer -- the winner of this game.
 */
void ReversiGame::finish(ReversiGamePlayer* winner) {
    if(!started || finished)
        return;

    finished = true;
    GAME_OVER_EVENT(this, new GameOverEventArgs(winner));
}

/**
 * addPlayer(IClient client).
 *
 * @param client IClient -- a client type.
 */
void ReversiGame::addPlayer(IClient* client) {
    // create a new game player with client specifier and color
    // Color convention: WHITE = 0, BLACK = 1, hence the % 2 for players.size()
    players.push_back(
            new ReversiGamePlayer(client, (Cell) ((int) players.size() % 2)));

    // 2 players have entered this game -> start it
    if (players.size() == 2)
        start();
}

/**
 * closeGame(IClient client).
 *
 * @param client IClient -- a client type.
 */
void ReversiGame::closeGame(IClient* client) {
    ReversiGamePlayer* player = getPlayerByClient(client);

    // remove the reference to all players from this game
    for(unsigned i = 0; i < players.size(); ++i) {
        players.erase(players.begin() + i);
    }

    // all players left -- close game
    if(players.empty())
        close();
}

/**
 * playMove(IClient client, CellIndex cI).
 *
 * @param client IClient -- a client.
 * @param cI CellIndex -- a move to make.
 * @return false in case of an exception throw
 */
bool ReversiGame::playMove(IClient* client, CellIndex cI) {
    LINFO << "Playing move by: " << client->getSocket();
    if(!started) {
        EXCEPTION("Game has NOT started yet!", client);
        return false;
    }

    if(finished) {
        EXCEPTION("Game is already over!", client);
        return false;
    }

    if(!legalMove(cI)) {
        PLAYER_ILLEGAL_MOVE(this, client);
        return false;
    }

    LINFO << "Move by: " << client->getSocket() << " is legal";

    ReversiGamePlayer* player = getPlayerByClient(client);

    if(player->getColor() != turnsManager->getCurrentPlayerColor()) {
        EXCEPTION("This is NOT your turn!", client);
        return false;
    }

    this->gameBoard->moveMade(cI, player->getColor());

    checkWin(player);

    // game continues - evaluate moves and pass the turn
    this->turnsManager->evaluateAvailableMovesForThisTurn(gameBoard);
    this->turnsManager->endTurn();

    // update players that a move has been made
    PLAYER_MOVED_EVENT(this, client, cI);
    return true;
}

/**
 * legalMove(CellIndex cI).
 *
 * @param cI CellIndex -- an indication for a move.
 * @return true if the move is inside this turnsManager's available moves, or false otherwise.
 */
bool ReversiGame::legalMove(CellIndex cI) {
    // Local Variables
    std::vector<CellIndex> availableMoves = turnsManager->getAvailableMoves();

    for(unsigned i = 0; i < availableMoves.size(); ++i) {
        if(cI.getRow() == availableMoves[i].getRow() && cI.getCol() == availableMoves[i].getCol())
            return true;
    }

    return false;
}

/**
 * checkWin(ReversiGamePlayer player).
 *
 * @param player ReversiGamePlayer -- check if this player has won.
 */
void ReversiGame::checkWin(ReversiGamePlayer* player) {
    if(gameBoard->getSpaceLeft() == 0) {
        // player won the game
        finish(player);
    }

}

/**
 * containsClient(IClient client).
 *
 * param client IClient -- a client.
 * @return true if the client is playing in this game, or false otherwise.
 */
bool ReversiGame::containsClient(IClient* client) {
    for(unsigned i = 0; i < players.size(); ++i) {
        if (players[i]->getClient()->getSocket() == client->getSocket()) {
            return true;
        }
    }
    return false;
}