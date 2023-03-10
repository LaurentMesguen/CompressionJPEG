//
// Created by FU427LME on 10/03/2023.
//

#ifndef JPEGENCODER_RLE_H
#define JPEGENCODER_RLE_H

#include <vector>

using namespace std;

struct RLEItem {
    int value;
    int count;
};

struct RLEVector {

    vector <RLEItem> items;
};

class RLE {
public:
    static vector<RLEVector> encode(const vector<vector<int>>& vectors);
    static vector<vector<int>> decode(const vector<RLEVector>& vectors);
    static void print(const vector<RLEVector>& vectors);
};


#endif //JPEGENCODER_RLE_H
