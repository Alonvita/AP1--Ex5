/**
 * Project:    Ex4.
 * Author:  Alon Vita
 *   ID:    311233431
 *
 * Class GameUtilities.
 *
 */

#include "GameUtilities.h"

/**
 * clearDuplicatesValues(vector<CellIndex>* vec).
 *
 * @param vec vector<CellIndex>* -- a reference to a vector of cell indexes.
 *
 */
void clearDuplicatesValues(std::vector<CellIndex> *vec) {
    for (unsigned i = 0; i < (*vec).size(); ++i) {
        //Inner loop variables
        int rowI = (*vec).at(i).getRow();
        int colI = (*vec).at(i).getCol();

        for (unsigned j = i + 1; j < (*vec).size(); ++j) {
            //Inner loop variables
            int rowJ = (*vec).at(j).getRow();
            int colJ = (*vec).at(j).getCol();

            if (rowI == rowJ && colI == colJ) {
                (*vec).erase((*vec).begin() + j);
                --j;
            }
        }
    }
}