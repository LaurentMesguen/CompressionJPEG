/*************************************************
* Name     : DCT.cpp                             *
* Author   : MESGUEN Laurent                     *
* Created  : 08.03.23                            *
**************************************************/
#include "../include/DCT.h"



DCT::DCT()
{

}


// TODO : precompute the cosinus values to save time
// TODO : factorize the code
void DCT::computeDCT(const Matrix<>* in, Matrix<int>* out)
{
    double alpha_i, alpha_j, sum;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sum = 0.0;
            for (int k = 0; k < 8; k++) {
                for (int l = 0; l < 8; l++) {
                    alpha_i = (i == 0) ? 1.0 / sqrt(2) : 1.0;
                    alpha_j = (j == 0) ? 1.0 / sqrt(2) : 1.0;
                    sum += alpha_i * alpha_j * in->at(k,l) *
                           cos((2 * k + 1) * i * M_PI / (16)) *
                           cos((2 * l + 1) * j * M_PI / (16));
                }
            }
            out->setPixel(i, j,  (int)round(sum / 4.0));
        }
    }
}
