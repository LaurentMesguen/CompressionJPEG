/*************************************************
* Name     : Huffman.cpp                         *
* Author   : MESGUEN Laurent                     *
* Created  : 08.03.23                            *
**************************************************/

#include "../include/Huffman.h"
#include "../include/EncodingStrategy.h"
#include <map>
#include <string>

using namespace std;

// DC Luminance Huffman table
const map<std::string, int> dcLuminanceHuffmanTable = {
        {"00", 2},
        {"010", 3},
        {"011", 3},
        {"100", 3},
        {"101", 3},
        {"110", 3},
        {"1110", 4},
        {"11110", 5},
        {"111110", 6},
        {"1111110", 7},
        {"11111110", 8},
        {"111111110", 9}
};

// DC Luminance Huffman table
const map<std::string, int> dcChrominanceHuffmanTable = {
        {"00", 2},
        {"01", 2},
        {"10", 2},
        {"110", 3},
        {"1110", 4},
        {"11110", 5},
        {"111110", 6},
        {"1111110", 7},
        {"11111110", 8},
        {"111111110", 9},
        {"1111111110", 10},
        {"11111111110", 11}
};

// AC Huffman table
//const map<std::string, int> acLuminanceHuffmanTable = {
//                                                                                                                                                                                                                           16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16}
//};
//

//vector<string> Huffman::encode(const vector<vector<RLEItem>> *rleVectors) {
//    vector<string > encoded;
//    for (auto &rleVector : *rleVectors) {
//        encoded.push_back(encodeRLEItem(rleVector));
//    }
//    return encoded;
//}
//
//vector<RLEItem> Huffman::decode(const vector<string> *encodedVectors) {
//    vector<RLEItem> decoded;
//    for (auto &encodedVector : *encodedVectors) {
//        decoded.push_back(decodeRLEItem(encodedVector));
//    }
//    return decoded;
//}
//
//string Huffman::encodeRLEItem(const RLEItem &item) {
//    return to_string(item.value) + " " + to_string(item.count);
//}
