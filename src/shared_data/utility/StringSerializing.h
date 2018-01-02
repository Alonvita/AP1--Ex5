//
// Created by alonv on 12/29/2017.
//

#ifndef AP1_EX3_STRINGSERIALIZING_H
#define AP1_EX3_STRINGSERIALIZING_H

#include <string>
#include <vector>
#include <sstream>

#include "../../game/board/CellIndex.h"

std::vector<std::string> split(const std::string &str, char delim);
std::string intToString(int n);
std::string cellIndexToString(CellIndex cI);
std::string  clearAndCheckString(char msg[], int size);

#endif //AP1_EX3_STRINGSERIALIZING_H
