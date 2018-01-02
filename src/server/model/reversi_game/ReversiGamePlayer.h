//
// Created by alonv on 12/23/2017.
//

#ifndef AP1_EX3_REVERSIGAMEPLAYER_H
#define AP1_EX3_REVERSIGAMEPLAYER_H


#include "../../../game/board/Cell.h"
#include "../../IClient.h"

class ReversiGamePlayer {
public:
    ReversiGamePlayer(IClient* client, Cell color);

    IClient*    getClient();
    bool        equals(IClient* other);
    Cell        getColor();

private:
    Cell    color;
    IClient* client;
};


#endif //AP1_EX3_REVERSIGAMEPLAYER_H
