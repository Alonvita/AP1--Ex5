//
// Created by alonv on 12/23/2017.
//

#include "ListGameContainer.h"

/**
 * containsGame(std::string name).
 *
 * @param name string -- a string representing a game name.
 * @return true if a game exists under this name, or fast otherwise.
 */
bool ListGameContainer::containsGame(std::string name) {
    for (unsigned i = 0; i < games.size(); ++i) {
        if (games[i]->getName() == name) {
            return true;
        }
    }
    return false;
}

/**
 * containsGame(IClient client).
 *
 * @param client IClient -- a client.
 * @return true if the container contans a game with the client inside it, or
 *          false otherwise.
 */
bool ListGameContainer::containsGame(IClient* client) {
    for (unsigned i = 0; i < games.size(); ++i) {
        if(games[i]->containsClient(client))
            return true;
    }
    return false;
}

/**
 * containsGame(Game game).
 *
 * @param game Game -- a game.
 * @return true if this game exists, or false otherwise
 */
bool ListGameContainer::containsGame(ReversiGame *game) {
    containsGame(game->getName());
}

/***
 * getGame(string name).
 *
 * @param name string -- a game name.
 * @return a reference to the game with this name.
 */
ReversiGame *ListGameContainer::getGame(string name) {
    if (!containsGame(name))
        return nullptr;

    for (unsigned i = 0; i < games.size(); ++i) {
        if (games[i]->getName() == name) {
            return games[i];
        }
    }
}

/**
 * getGame(IClient client).
 *
 * @param client
 * @return if a game exists under this client's fd, or false otherwise
 */
ReversiGame *ListGameContainer::getGame(IClient* client) {
    for (unsigned i = 0; i < games.size(); ++i) {
        if (games[i]->getPlayerByClient(client)->getClient()->getSocket() == client->getSocket()) {
            return games[i];
        }
    }
}

/**
 * ListGameContainer::listGames().
 *
 * @return a vector containing all open games that have not started yet.
 */
std::vector<std::string> ListGameContainer::listGames() {
    // Local Variables
    std::vector<std::string> listGames;

    if(games.empty()) {
        listGames.push_back("There are no available game at the moment");
    } else {
        listGames.push_back("The available game are:\n");
    }

    for (unsigned i = 0; i < games.size(); ++i) {
        // game has already started -> ignore it
        if (games[i]->getStarted())
            continue;
        // push it's name
        listGames.push_back(games[i]->getName());
    }

    return listGames;
}

/**
 * addGame(ReversiGame *game).
 *
 * @param game ReversiGame -- a game reference to a game to add to the container list.
 */
void ListGameContainer::addGame(ReversiGame *game) {
    games.push_back(game);
}

/**
 * removeGame(ReversiGame *game).
 *
 * @param game ReversiGame -- a reference to a game to remove from the container list.
 */
void ListGameContainer::removeGame(ReversiGame *game) {
    for (unsigned i = 0; i < games.size(); ++i) {
        if (games[i]->getName() == game->getName()) {
            games.erase(games.begin() + i);
            return;
        }
    }
}