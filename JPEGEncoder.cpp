//
// Created by FU427LME on 08/03/2023.
//

#include <iostream>
#include "JPEGEncoder.h"

using namespace std;

JPEGEncoder::JPEGEncoder(Image *inputImage) : rgbImage(inputImage){

    yBlocks.resize(rgbImage->getWidth()*rgbImage->getHeight()/64);
    uBlocks.resize(rgbImage->getWidth()*rgbImage->getHeight()/64);
    vBlocks.resize(rgbImage->getWidth()*rgbImage->getHeight()/64);
}

void JPEGEncoder::encode()
{
    downsampling();
    decomposeBlock8Pixels();
    dct();
}

/***
 * These methods aim to apply a 4:2:2 downsampling on the color matrix (UV)
 *
 */
void JPEGEncoder::downsampling() {
    cout << "Downsampling color matrix (U/V)" << endl;
    downsampling(rgbImage->getU());
    downsampling(rgbImage->getV());
    cout << "Downsampling finished." << endl;
}

void JPEGEncoder::downsampling(Matrix &matrix) {


    uint32_t mean4Pixels;
    for (int i = 0; i < rgbImage->getHeight(); i+=2)
    {
        for (int j = 0; j < rgbImage->getWidth(); j+=2)
        {
            mean4Pixels = (matrix.at(i, j) + matrix.at(i+1, j) + matrix.at(i, j+1) + matrix.at(i+1, j+1)) / 4;

            matrix.setPixel(i, j, mean4Pixels);
            matrix.setPixel(i+1, j, mean4Pixels);
            matrix.setPixel(i, j+1, mean4Pixels);
            matrix.setPixel(i+1, j+1, mean4Pixels);
        }
    }

}

/***
*  These methods aim to decompose the image in blocks of 8*8 pixels.
*/

void JPEGEncoder::decomposeBlock8Pixels() {
    cout << "8*8 pixels blocks decomposition..." << endl;
    decomposeBlock8Pixels(rgbImage->getY(), yBlocks);
    decomposeBlock8Pixels(rgbImage->getU(), uBlocks);
    decomposeBlock8Pixels(rgbImage->getV(), vBlocks);
}

void JPEGEncoder::decomposeBlock8Pixels(const Matrix& in, vector<Matrix>& out )
{

    if (in.getHeight() % 8 != 0 ||  in.getWidth() % 8 != 0)
    {
        throw runtime_error("The image provided cannot be decomposed in blocks of 8*8 pixels.");
    }

    for (int row=0; row < in.getHeight(); row+=8)
    {
        for (int col = 0; col < in.getWidth(); col+=8)
        {
            Matrix mat;
            mat.resize(8, 8);
            mat.setPixel(0, 0, 0);
            for (int i = 0; i < 8; i++)
            {
                for(int j = 0; j < 8; j++)
                {
                    mat.setPixel(i, j, in.at(i+row, j+col));
                    //cout << "(" << i-row << ", " << j-col << ") - (" << i << ", " << j << ")" << endl;
                }
            }
            out.push_back(mat);
        }
    }
    cout << "8*8 pixels blocks decomposition done." << endl;
}

void JPEGEncoder::dct()
{
    dct(yBlocks);
    dct(uBlocks);
    dct(vBlocks);
}

void JPEGEncoder::printBlocks(const vector<Matrix>& blocks) {
    for(int i =0; i< blocks.size(); i++)
    {
        blocks.at(i).print();
        cout << endl;
    }
}

void JPEGEncoder::printBlocks() {
    printBlocks(yBlocks);
    printBlocks(uBlocks);
    printBlocks(vBlocks);
}