//
// Created by alonv on 12/23/2017.
//

#include "ReversiGameEvent.h"

/**
 * GameOverEventArgs(IClient winner).
 *
 * @param winner IClient -- the winner of a game.
 */
GameOverEventArgs::GameOverEventArgs(ReversiGamePlayer* winner) {
    this->winner = winner;
}

/**
 * GameOverEventArgs::getWinner().
 *
 * @return the winner of the game.
 */
ReversiGamePlayer* GameOverEventArgs::getWinner() {
    return this->winner;
}