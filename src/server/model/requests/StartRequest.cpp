//
// Created by alonv on 12/23/2017.
//

#include "StartRequest.h"

/**
 * getClient().
 *
 * @return the client who sent this request.
 */
IClient* StartRequest::getClient() {
    return this->client;
}

/**
 * getName().
 *
 * @return the game to start name.
 */
std::string StartRequest::getName() {
    return this->name;
}
