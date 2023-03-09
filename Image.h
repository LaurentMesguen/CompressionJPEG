/*************************************************
* Name     : Image.h                             *
* Author   : MESGUEN Laurent                     *
* Created  : 08.03.23                            *
**************************************************/

#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <vector>
#include <string>
#include "Matrix.h"

using namespace std;

/*** This class aim to represent  ***/
class Image {

private :

    string filename;
    // RGB
    Matrix<> r;
    Matrix<> g;
    Matrix<> b;
    // YUV
    Matrix<> y;
    Matrix<> u;
    Matrix<> v;

    int height;
    int width;
    int fileSize;

public:
    Image();
    Image(const Image&);
    ~Image();

    void readFromFile (string filename);
    void printRGB();
    void printYUV();
    int getFileSize() const {return fileSize;}
    int getHeight() const {return height;}
    int getWidth() const {return width;}
    string getFilename() const {return filename;}
    // RGB
    Matrix<>& getR()  {return r;}
    Matrix<>& getG()  {return g;}
    Matrix<>& getB()  {return b;}
    // YUV
    Matrix<>& getY()  {return y;}
    Matrix<>& getU()  {return u;}
    Matrix<>& getV()  {return v;}
};



#endif // IMAGE_H_INCLUDED
