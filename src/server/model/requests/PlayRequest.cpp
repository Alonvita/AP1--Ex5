//
// Created by alonv on 12/23/2017.
//

#include "PlayRequest.h"

/**
 * PlayRequest(IClient c, CellIndex Move).
 *
 * @param c IClient -- a client type.
 * @param Move CellIndex -- a cell index
 */
PlayRequest::PlayRequest(IClient* c, CellIndex move) {
    this->client = c;
    this -> move = move;
}

/**
 * getClient().
 *
 * @return the client who sent this request.
 */
IClient* PlayRequest::getClient() {
    return this->client;
}

/**
 * getMove().
 *
 * @return the move request of this message.
 */
CellIndex PlayRequest::getMove() {
    return this->move;
}