//
// Created by alonv on 12/29/2017.
//

#include "MoveUpdate.h"
#include "utility/StringSerializing.h"

/**
 *
 * @return
 */
std::string MoveUpdate::toString() {
    std::string moveAsString;

    moveAsString = "[" + gameName + "], ";
    moveAsString += "a move was made: ";
    moveAsString += "(";
    moveAsString += intToString(cI.getRow());
    moveAsString += ",";
    moveAsString += intToString(cI.getCol());
    moveAsString += ")";

    return moveAsString;
}

/**
 * fromString().
 *
 * @return a CellIndex representing the given string
 */
CellIndex MoveUpdate::fromString(std::string str) {
    if (str.size() != 3)
        std::runtime_error("Error: bad string inserted!");

    // return a cell index representing the given string
    return CellIndex(str[0], str[2]);
}

/**
 * getName().
 *
 * @return the name of the game to update move on.
 */
std::string MoveUpdate::getName() {
    return this->gameName;
}

/**
 * getMove().
 *
 * @return the move to update as CellIndex.
 */
CellIndex MoveUpdate::getMove() {
    return this->cI;
}