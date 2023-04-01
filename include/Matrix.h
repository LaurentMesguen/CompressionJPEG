//
// Created by FU427LME on 08/03/2023.
//

#ifndef COMPRESSIONJPEGCPP_MATRIX_H
#define COMPRESSIONJPEGCPP_MATRIX_H

using namespace std;

#include <vector>
#include <cstdint>
#include <iostream>
#include <iomanip>


template <class T=uint8_t >
class Matrix{
private:
    vector<T> matrix;
    int height;
    int width;
public :
    Matrix();
    Matrix(int height, int width);
    Matrix(const vector<T> &vector);
    Matrix(const Matrix<T> &matrix);
    int getHeight() const {return height;}
    int getWidth() const {return width;}
    void print() const;
    void printSignedNumber() const;
    T at(int x, int y) const {return matrix[y+x*width];}
    void setPixel(int x, int y, T value);
    void resize(int height, int width) ;
    bool operator==(const Matrix<T> &matrix) const {
        return this->matrix == matrix.matrix;
    }
    bool operator==(const vector<T> &vector) const {
        return this->matrix == vector;
    }
};

template<class T> Matrix<T>::Matrix() : Matrix(0, 0) {}

template<class T> Matrix<T>::Matrix(int height, int width) : height(height), width(width) { matrix.resize(8*8);}

template<class T> Matrix<T>::Matrix( const vector<T> &vector ) { this->matrix = vector; }

template<class T> Matrix<T>::Matrix(const Matrix<T> &matrix) {
    this->matrix = matrix.matrix;
    this->height = matrix.height;
    this->width = matrix.width;
}

template<class T> void Matrix<T>::resize(int height, int width){
    this->height = height;
    this->width = width;
    matrix.resize(height * width);
}

template<class T> void Matrix<T>::setPixel(int x, int y, T value) {
    matrix[y+x*width] = value;
}

template<class T> void Matrix<T>::print() const {

    cout << "[";
    for (int x = 0 ; x < height ; x++) {
        cout << "[";
        for(int y= 0; y < width; y++) {
            cout << setw(3) << setfill('0') << (int) at(x, y) << ",";
        }
        cout << "]";
        cout << endl;
    }
    cout << "]";
    cout << endl;
}



template<class T> void Matrix<T>::printSignedNumber() const {

    for (int x = 0 ; x < height ; x++) {
        for(int y= 0; y < width; y++) {
            cout << setw(4) << setfill(' ') << at(x, y) << " ";
        }
        cout << endl;
    }
    cout << endl;
}


#endif //COMPRESSIONJPEGCPP_MATRIX_H
