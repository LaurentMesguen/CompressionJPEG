/*************************************************
* Name     : Image.cpp                           *
* Author   : MESGUEN Laurent                     *
* Created  : 08.03.23                            *
**************************************************/

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Image.h"

using namespace std;

void Image::readFromFile(string filename) {

    cout << "Reading bitmap file " << filename << endl;
    ifstream file{ filename, std::ios_base::binary };
    if(!file)
    {
        throw std::runtime_error (string("Cannot open the image ") + filename );
    }

    const int fileHeaderSize = 14;
    const int infoHeaderSize = 40;

    unsigned char fileHeader[fileHeaderSize];
    file.read(reinterpret_cast<char*>(fileHeader), fileHeaderSize);

    unsigned char infoHeader[infoHeaderSize];
    file.read(reinterpret_cast<char*>(infoHeader), infoHeaderSize);

    if( fileHeader[0] != 0x42 || fileHeader[1] != 0x4D) {
        throw std::runtime_error("Error! Unrecognized file format.");
    }

    fileSize = fileHeader[2] + (fileHeader[3] << 8 ) + (fileHeader[4] << 16) + (fileHeader[5] << 24);
    width = infoHeader[4] + (infoHeader[5] << 8) + (infoHeader[6] << 16) + (infoHeader[7] << 24);
    height = infoHeader[8] + (infoHeader[9] << 8) + (infoHeader[10] << 16) + (infoHeader[11] << 24);

    cout << "File size = " << fileSize << " bytes" << endl;
    cout << "Height : " << height << " pixels." << endl;
    cout << "Width : " << width << " pixels." << endl;

    r.resize(height, width);
    g.resize(height , width);
    b.resize(height , width);

    y.resize(height , width);
    u.resize(height , width);
    v.resize(height , width);

    for(int i = height-1; i >= 0; i--)
    {
        for (int j = 0; j < width; j++)
        {
            uint8_t color[3];
            file.read(reinterpret_cast<char*>(color), 3);
            r.setPixel(i, j , color[2]);
            g.setPixel(i, j , color[1]);
            b.setPixel(i, j , color[0]);

            /* **************************************
            Y =  0.299*R + 0.587*G + 0.114*B
            U = -0.169*R - 0.331*G + 0.500*B + 128.0
            V =  0.500*R - 0.419*G - 0.081*B + 128.0
            ****************************************/

            /* YUV shifted around zero (minus 128) */

            y.setPixel(i, j, 0.299*color[2] + 0.587*color[1] + 0.114*color[0] - 128.0);
            u.setPixel(i, j,  -0.169*color[2] - 0.331*color[1] + 0.500*color[0]);
            v.setPixel(i, j,  0.500*color[2] - 0.419*color[1] - 0.081*color[0]);
        }
    }

    cout << "File successfully read!" << endl;
}

Image::Image() : filename(""), fileSize(0), height(0), width(0){

}

Image::Image(const Image &image) : filename(image.filename), r(image.r), g(image.g), b(image.b), fileSize(image.fileSize) {

}

Image::~Image() {
}

void Image::printRGB() {

    cout << "R Matrix : " << endl;
    r.print();
    cout << "G Matrix : " << endl;
    g.print();
    cout << "B Matrix : " << endl;
    b.print();
}

void Image::printYUV() {

    cout << "Y Matrix : " << endl;
    y.print();
    cout << "U Matrix : " << endl;
    u.print();
    cout << "V Matrix : " << endl;
    v.print();
}