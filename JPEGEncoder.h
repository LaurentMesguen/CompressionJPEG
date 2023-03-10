//
// Created by FU427LME on 08/03/2023.
//

#ifndef COMPRESSIONJPEGCPP_JPEGENCODER_H
#define COMPRESSIONJPEGCPP_JPEGENCODER_H


#include "Image.h"

#include "Quantization.h"

//enum EncodingType


class JPEGEncoder {

private:
    Image* rgbImage;
    vector<Matrix<>> yBlocks;
    vector<Matrix<>> uBlocks;
    vector<Matrix<>> vBlocks;

    vector<Matrix<int>> yBlocksAfterDCT;
    vector<Matrix<int>> uBlocksAfterDCT;
    vector<Matrix<int>> vBlocksAfterDCT;

    vector<vector<int>> yVectorsAfterZigZagScan;
    vector<vector<int>> uVectorsAfterZigZagScan;
    vector<vector<int>> vVectorsAfterZigZagScan;
    void downsampling();
    void downsampling(Matrix<>& matrix);
    void decomposeBlock8Pixels();
    void decomposeBlock8Pixels(const Matrix<>& in, vector<Matrix<>>& out );
    void initMatrix(vector<Matrix<int>>* mat, int size);
    void printBlocks(const vector<Matrix<>>& blocks);
    void printBlocksAfterDCT(const vector<Matrix<int>>& blocks);
    void dct();
    void dct(vector <Matrix<>> &in, vector <Matrix<int>> &out);
    void quantization();
    void quantization(vector<Matrix<int>> * mat, QuantizationType type);
    void zigZagScan();
    vector<int> zigZagScan(const Matrix<int>& in);
    void zigZagScan(const vector<Matrix<int>>& in, vector<vector<int>>& out);
    void printVectors(const vector<vector<int>>& vectors);
    void printVector(const vector<int>& vec);

public:
    JPEGEncoder(Image* inputImage);
    //~JPEGEncoder();
    void printBlocks();
    void printBlocksAfterDCT();
    void printVectors();

    void encode();

};


#endif //COMPRESSIONJPEGCPP_JPEGENCODER_H
