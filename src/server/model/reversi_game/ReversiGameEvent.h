//
// Created by alonv on 12/23/2017.
//

#ifndef AP1_EX3_REVERSIGAMEEVENT_H
#define AP1_EX3_REVERSIGAMEEVENT_H

#include "ReversiGame.h"
#include "../../IClient.h"
#include "../../../game/board/Cell.h"

class GameOverEventArgs {
public:
    GameOverEventArgs() : winner(nullptr) {};
    GameOverEventArgs(ReversiGamePlayer *winner);
    ~GameOverEventArgs() {}

    ReversiGamePlayer *getWinner();

private:
    ReversiGamePlayer *winner = nullptr;
};

#endif //AP1_EX3_REVERSIGAMEEVENT_H
