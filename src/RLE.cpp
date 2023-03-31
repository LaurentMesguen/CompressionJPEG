//
// Created by FU427LME on 10/03/2023.
//

#include <iostream>
#include "../include/RLE.h"

std::vector<RLEItem> RLE::encodeVector(const std::vector<int>& input) {
    std::vector<RLEItem> encoded;
    int zeroCount = 0;

    for (size_t i = 0; i < input.size(); i++) {
        if (input[i] == 0)
        {
            if(zeroCount == 15)
            {
                encoded.push_back(ZRL);
                zeroCount = 0;
            }
            else
                zeroCount++;
        }
        else {
            encoded.push_back(RLEItem{input[i], zeroCount});
            zeroCount = 0;
        }
    }

    encoded.push_back(EOB);

    // remove all ZRL before EOB
    for (int i = encoded.size() - 2; i >= 0; i--) {
        if (encoded[i].value == 0 && encoded[i].zeroCount == 15) {
            encoded.erase(encoded.begin() + i);
        } else {
            break;
        }
    }

    return encoded;
}

std::vector<int> RLE::decodeVector(const std::vector<RLEItem>& encoded) {
    std::vector<int> decoded;

    for (size_t i = 0; i < encoded.size(); i++) {
        if (encoded[i].value == 0 && encoded[i].zeroCount == 0) {
            break;
        } else if (encoded[i].value == 0 && encoded[i].zeroCount == 15) {
            for (int j = 0; j < 16; j++) {
                decoded.push_back(0);
            }
        } else {
            for (int j = 0; j < encoded[i].zeroCount; j++) {
                decoded.push_back(0);
            }
            decoded.push_back(encoded[i].value);
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