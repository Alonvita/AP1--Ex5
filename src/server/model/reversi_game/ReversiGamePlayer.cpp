//
// Created by alonv on 12/23/2017.
//

#include "ReversiGamePlayer.h"


/**
 * ReversiGamePlayer(IClient client, Cell color).
 *
 * @param client IClient -- a client.
 * @param color Cell -- a color.
 */
ReversiGamePlayer::ReversiGamePlayer(IClient* client, Cell color) : client(client), color(color) {}

/**
 * getColor().
 *
 * @return this player's color
 */
Cell ReversiGamePlayer::getColor() {
    return this->color;
}

/**
 * getFD().
 *
 * @return a reference to the client representing this player
 */
IClient* ReversiGamePlayer::getClient() {
    return this->client;
}

/**
 * equals(IClient other).
 *
 * @param other IClient -- another client
 * @return true if the FDs are equal, or fase otherwise.
 */
bool ReversiGamePlayer::equals(IClient* other) {
    return (this->client)->getSocket() == other->getSocket();
}