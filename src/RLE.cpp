/*************************************************
* Name     : RLE.cpp                             *
* Author   : MESGUEN Laurent                     *
* Created  : 08.03.23                            *
**************************************************/

#include <iostream>
#include "../include/RLE.h"

std::vector<RLEItem> RLE::encodeVector(const std::vector<int>& input) {
    std::vector<RLEItem> encoded;
    int runLength = 0;

    for (size_t i = 0; i < input.size(); i++) {
        if (input[i] == 0)
        {
            if(false && runLength == 15) // TODO replace the false with the boolean isZRLEnabled
            {
                encoded.push_back(ZRL);
                runLength = 0;
            }
            else
                runLength++;
        }
        else {
            encoded.push_back(RLEItem{runLength, input[i] });
            runLength = 0;
        }
    }

    encoded.push_back(EOB);

    // remove all ZRL before EOB
    if(false) // TODO replace the false with the boolean isZRLEnabled
    {
        for (int i = encoded.size() - 2; i >= 0; i--) {
            if (encoded[i].run == 0 && encoded[i].size == 15) {
                encoded.erase(encoded.begin() + i);
            } else {
                break;
            }
        }
    }

    return encoded;
}

std::vector<int> RLE::decodeVector(const std::vector<RLEItem>& encoded) {
    std::vector<int> decoded;

    for (size_t i = 0; i < encoded.size(); i++) {
        if (encoded[i].run == 0 && encoded[i].size == 0) {
            break;
        } else if (encoded[i].run == 0 && encoded[i].size == 15) {
            for (int j = 0; j < 16; j++) {
                decoded.push_back(0);
            }
        } else {
            for (int j = 0; j < encoded[i].size; j++) {
                decoded.push_back(0);
            }
            decoded.push_back(encoded[i].run);
        }
    }

    return decoded;
}


vector<RLEVector> RLE::encode(const vector<vector<int>> &vectors) {
    vector<RLEVector> rleVectors;
    for (int i = 0; i < vectors.size(); ++i) {
        rleVectors.push_back(encodeVector(vectors.at(i)));
    }
    return rleVectors;
}

vector<vector<int>> RLE::decode(const vector<RLEVector> &rleVectors) {
    vector<vector<int>> vectors;
    for (int i = 0; i < vectors.size(); ++i) {
        vectors.push_back(decodeVector(rleVectors.at(i)));
    }
    return vectors;
}

void RLE::print(const vector<RLEVector> &vectors) {
    for (int i = 0; i < vectors.size(); ++i) {
        cout << "Vector " << i << ": ";
        for (int j = 0; j < vectors.at(i).size(); ++j) {
            cout << vectors.at(i).at(j).value << " ";
        }
        cout << endl;
    }
}
