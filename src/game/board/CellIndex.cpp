//
// Created by alonv on 12/23/2017.
//
#include "CellIndex.h"
#include "../../shared_data/utility/StringSerializing.h"

CellIndex::CellIndex() {
    this->row = -1;
    this->col = -1;
}

CellIndex::CellIndex(int row, int col) {
    this->row = row;
    this->col = col;
}

/**
 * getRow().
 *
 * @return the row that this index is on.
 */
int CellIndex::getRow() {
    return this->row;
}

/**
 * getCol().
 *
 * @return the col that this index is on.
 */
int CellIndex::getCol() {
    return this->col;
}

void CellIndex::setRow(int row) {
    this->row = row;
}

void CellIndex::setCol(int col) {
    this->col = col;
}

/**
 * toSTring().
 *
 * @return a string representation of this CellIndex.
 */
std::string CellIndex::toString() {
    std::string move;
    std::string row = intToString(this->getRow() + 1);
    std::string col = intToString(this->getCol() + 1);

    //Iter over available moves and print them

    move = "(";
    move += row;
    move += ",";
    move += col;
    move += ")";

    return move;
}

/**
 * fromString(std::string str).
 */
void CellIndex::fromString(std::string str) {
    if(str.size() != 3)
        row = col = -1;

    const char* strToChars = str.c_str();

    if(!('0' < strToChars[0] && strToChars[2] < '9'))
        row = col = -1;

    row = (strToChars[0] - '0');
    row--;
    col = (strToChars[2] - '0');
    col --;
}