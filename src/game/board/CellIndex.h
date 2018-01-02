//
// Created by alonv on 12/23/2017.
//

#ifndef AP1_EX3_CELLINDEX_H
#define AP1_EX3_CELLINDEX_H

#include <cstdio>
#include <string>

class CellIndex {
public:
    CellIndex();
    CellIndex(int row, int col);

    int getRow();
    int getCol();
    void setRow(int row);
    void setCol(int row);

    void        fromString(std::string str);
    std::string toString();

private:
    int row;
    int col;
};


#endif //AP1_EX3_CELLINDEX_H
