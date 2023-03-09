//
// Created by FU427LME on 08/03/2023.
//

#ifndef COMPRESSIONJPEGCPP_JPEGENCODER_H
#define COMPRESSIONJPEGCPP_JPEGENCODER_H


#include "Image.h"


//enum EncodingType


class JPEGEncoder {

private:
    Image* rgbImage;
    vector<Matrix<>> yBlocks;
    vector<Matrix<>> uBlocks;
    vector<Matrix<>> vBlocks;

    vector<Matrix<double>> yBlocksAfterDCT;
    vector<Matrix<double>> uBlocksAfterDCT;
    vector<Matrix<double>> vBlocksAfterDCT;
    void downsampling();
    void downsampling(Matrix<>& matrix);
    void decomposeBlock8Pixels();
    void decomposeBlock8Pixels(const Matrix<>& in, vector<Matrix<>>& out );
    void initMatrix(vector<Matrix<double>>* mat, int size);
    void printBlocks(const vector<Matrix<>>& blocks);
    void printBlocksAfterDCT(const vector<Matrix<double>>& blocks);
    void dct();
    void dct(vector <Matrix<>> &in, vector <Matrix<double>> &out);
    void quantization();
    void quantization(vector<Matrix<double>> * mat);

public:
    JPEGEncoder(Image* inputImage);
    //~JPEGEncoder();
    void printBlocks();
    void printBlocksAfterDCT();

    void encode();

};


#endif //COMPRESSIONJPEGCPP_JPEGENCODER_H
