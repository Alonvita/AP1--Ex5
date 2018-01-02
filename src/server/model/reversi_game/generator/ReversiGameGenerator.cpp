//
// Created by alonv on 12/23/2017.
//

#include "ReversiGameGenerator.h"

/**
 * generateGame(int boardType, int gameMode).
 *
 * @return
 */
void *ReversiGameGenerator::generateGame(std::string name) {
    ReversiGame *game = new ReversiGame(name);

    return (void *) game;
}