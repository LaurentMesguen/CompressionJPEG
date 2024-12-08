/*************************************************
* Name     : DPCM.cpp                            *
* Author   : MESGUEN Laurent                     *
* Created  : 08.03.23                            *
**************************************************/

#include "../include/DPCM.h"

void DPCM::encode(vector<Matrix<int>> &vectors) {

    int previous = 0;
    for (auto &vector : vectors) {
        vector.setPixel(0, 0,vector.at(0, 0) - previous);
        previous = vector.at(0, 0);
    }
}

void DPCM::decode(vector<Matrix<int>> &vectors) {
    int previous = 0;
    for (auto &vector : vectors) {
        vector.setPixel(0, 0,vector.at(0, 0) + previous);
        previous = vector.at(0, 0);
    }
}
