//
// Created by FU427LME on 08/03/2023.
//

#ifndef COMPRESSIONJPEGCPP_MATRIX_H
#define COMPRESSIONJPEGCPP_MATRIX_H

using namespace std;

#include <vector>
#include <cstdint>

class Matrix{
private:
    vector<uint8_t> matrix;
    int height;
    int width;
public :
    Matrix();
    Matrix(int height, int width);
    int getHeight() const {return height;}
    int getWidth() const {return width;}
    void print() const;
    uint32_t at(int x, int y) const {return matrix[y+x*width];}
    void setPixel(int x, int y, uint8_t value);
    void resize(int height, int width) ;
};


#endif //COMPRESSIONJPEGCPP_MATRIX_H
