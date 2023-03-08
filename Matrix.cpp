//
// Created by FU427LME on 08/03/2023.
//

#include <iostream>
#include <iomanip>
#include "Matrix.h"



Matrix::Matrix() : Matrix(0, 0) {}

Matrix::Matrix(int height, int width) : height(height), width(width) {}

void Matrix::resize(int height, int width){
    this->height = height;
    this->width = width;
    matrix.resize(height * width);
}

void Matrix::setPixel(int x, int y, uint8_t value) {
    matrix[y+x*width] = value;
}

void Matrix::print() const {

    for (int y = 0 ; y < width ; y++) {
        for(int x= 0; x < height; x++) {
            cout << setw(3) << setfill('0') << (int) at(x, y) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

