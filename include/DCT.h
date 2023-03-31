//
// Created by FU427LME on 08/03/2023.
//

#ifndef JPEGENCODER_DCT_H
#define JPEGENCODER_DCT_H


#include <cmath>
#include <cstdint>
#include "Matrix.h"


class DCT {

public:

    DCT();
    static void computeDCT(const Matrix<>* in, Matrix<int>* out);
};


#endif //JPEGENCODER_DCT_H
