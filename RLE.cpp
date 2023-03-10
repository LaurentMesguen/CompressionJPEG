//
// Created by FU427LME on 10/03/2023.
//

#include <iostream>
#include "RLE.h"

vector<RLEVector> RLE::encode(const vector<vector<int>> &vectors) {
    vector<RLEVector> rleVectors;
    for (int i = 0; i < vectors.size(); ++i) {
        RLEVector rleVector;
        int count = 1;
        for (int j = 0; j < vectors.at(i).size(); ++j) {
            if (j == vectors.at(i).size() - 1) {
                rleVector.items.push_back({vectors.at(i).at(j), count});
            } else if (vectors.at(i).at(j) == vectors.at(i).at(j + 1)) {
                count++;
            } else {
                rleVector.items.push_back({vectors.at(i).at(j), count});
                count = 1;
            }
        }
        rleVectors.push_back(rleVector);
    }
    return rleVectors;
}

void RLE::print(const vector<RLEVector> &vectors) {
    for (int i = 0; i < vectors.size(); ++i) {
        cout << "Vector " << i << ": ";
        for (int j = 0; j < vectors.at(i).items.size(); ++j) {
            cout << "(" << vectors.at(i).items.at(j).value << ", " << vectors.at(i).items.at(j).count << ") ";
        }
        cout << endl;
    }
}