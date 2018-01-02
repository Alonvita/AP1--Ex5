//
// Created by alonv on 12/23/2017.
//

#ifndef AP1_EX3_PLAYREQUEST_H
#define AP1_EX3_PLAYREQUEST_H


#include <string>
#include "../../IClient.h"
#include "../../../game/board/CellIndex.h"

class PlayRequest {
public:
    PlayRequest(IClient* client, CellIndex move);

    IClient*    getClient();
    CellIndex   getMove();

private:
    IClient*    client;
    CellIndex   move;
};


#endif //AP1_EX3_PLAYREQUEST_H
