//
// Created by alonv on 12/29/2017.
//

#ifndef AP1_EX3_MOVEUPDATE_H
#define AP1_EX3_MOVEUPDATE_H

#include <stdexcept>

#include "../game/board/CellIndex.h"

class MoveUpdate {
public:
    MoveUpdate(std::string gameName, CellIndex cI) : gameName(gameName), cI(cI) {};

    std::string toString();
    CellIndex fromString(std::string str);

    CellIndex getMove();
    std::string getName();
private:
    std::string gameName;
    CellIndex cI;
};


#endif //AP1_EX3_MOVEUPDATE_H
