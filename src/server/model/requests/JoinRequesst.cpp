//
// Created by alonv on 12/23/2017.
//

#include "JoinRequest.h"

/**
 * getClient().
 *
 * @return the client who sent this request.
 */
IClient* JoinRequest::getClient() {
    return this->client;
}

/**
 * getName().
 *
 * @return the game to join name.
 */
std::string JoinRequest::getName() {
    return this->name;
}
