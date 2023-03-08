//
// Created by FU427LME on 08/03/2023.
//

#ifndef COMPRESSIONJPEGCPP_JPEGENCODER_H
#define COMPRESSIONJPEGCPP_JPEGENCODER_H


#include "Image.h"

class JPEGEncoder {

private:
    Image* rgbImage;
    vector<Matrix> yBlocks;
    vector<Matrix> uBlocks;
    vector<Matrix> vBlocks;
    void downsampling();
    void downsampling(Matrix& matrix);
    void decomposeBlock8Pixels();
    void decomposeBlock8Pixels(const Matrix& in, vector<Matrix>& out );
    void printBlocks(const vector<Matrix>& blocks);
    void dct();
    void dct(vector<Matrix>& blocks);

public:
    JPEGEncoder(Image* inputImage);
    //~JPEGEncoder();
    void printBlocks();

    void encode();

};


#endif //COMPRESSIONJPEGCPP_JPEGENCODER_H
