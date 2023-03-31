//
// Created by FU427LME on 10/03/2023.
//

#ifndef JPEGENCODER_RLE_H
#define JPEGENCODER_RLE_H

#include <vector>
#include <deque>

using namespace std;

struct RLEItem {
    int value;
    int zeroCount;
};

using RLEVector = vector <RLEItem>;

const RLEItem EOB = {0, 0};
const RLEItem ZRL = {0, 15};

class RLE {
public:
    static vector<RLEVector> encode(const vector<vector<int>>& vectors);
    static vector<vector<int>> decode(const vector<RLEVector>& vectors);
    static RLEVector encodeVector(const vector<int>& input);
    static vector<int> decodeVector(const vector<RLEItem>& encoded);
    static void print(const vector<RLEVector>& vectors);
};


#endif //JPEGENCODER_RLE_H
