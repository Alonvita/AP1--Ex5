//
// Created by alonv on 12/23/2017.
//

#include "CloseRequest.h"

/**
 * getClient().
 *
 * @return the client who sent this request.
 */
IClient* CloseRequest::getClient() {
    return this->client;
}

/**
 * getName().
 *
 * @return the game to close name.
 */
std::string CloseRequest::getName() {
    return this->name;
}