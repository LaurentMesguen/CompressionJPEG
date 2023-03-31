//
// Created by FU427LME on 10/03/2023.
//

#ifndef JPEGENCODER_ENCODINGSTRATEGY_H
#define JPEGENCODER_ENCODINGSTRATEGY_H

#include <string>
#include "RLE.h"

//enum EncodingType {
//    eHuffmanStatic,
//    eHuffmanHalfAdaptive,
//    eHuffmanFullAdaptive,
//    eBAC
//};

class EncodingStrategy {

public:
    virtual vector<string> encode(const vector<vector<RLEItem>> *rleVectors) = 0;
    virtual vector<vector<RLEItem>> decode(const vector<string> *encodedVectors) = 0;

};




#endif //JPEGENCODER_ENCODINGSTRATEGY_H
