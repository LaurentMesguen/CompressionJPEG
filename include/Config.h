//
// Created by FU427LME on 05/03/2023.
//

#ifndef COMPRESSIONJPEGC___CONFIG_H
#define COMPRESSIONJPEGC___CONFIG_H

#include <string>

using namespace std;

enum EncodingType
{
    eUnknownEncodingType,
    eHuffmanStaticPerImage, // huffman statique par image
    eHuffmanAdaptativePerImage, // huffman adaptatif par image
    eHuffmanAdaptativePerBlock, // huffman adaptatif par bloc
    eBACStaticPerImage, // BAC statique par image
    eBACHalfAdaptative, // BAC semi_adaptatif
    eBACAdaptativePerImage // BAC adaptatif par image
};


class Config {
private:
    string configFilePath;
    string imageFilename;
    int quantificationPace;
    EncodingType encodingType;

public:
    Config(string path);
    void load();
    string getImageFilename() const {return imageFilename;}
    int getQuantificationPace() const {return quantificationPace;}
    EncodingType getEncodingType() const {return encodingType;}
    string getStringEncodingType();
};


#endif //COMPRESSIONJPEGC___CONFIG_H
