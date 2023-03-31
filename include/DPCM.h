//
// Created by FU427LME on 11/03/2023.
//

#ifndef JPEGENCODER_DPCM_H
#define JPEGENCODER_DPCM_H

#include <vector>
#include "Matrix.h"

using namespace std;

class DPCM {

public:
    static void encode( vector<Matrix<int>>& vectors);
    static void decode( vector<Matrix<int>>& vectors);
    static void print(const vector<vector<int>>& vectors);
};


#endif //JPEGENCODER_DPCM_H
