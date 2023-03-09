//
// Created by FU427LME on 08/03/2023.
//

#include <iostream>
#include "JPEGEncoder.h"
#include "DCT.h"

using namespace std;

/***
 *
 * @param inputImage
 */

JPEGEncoder::JPEGEncoder(Image *inputImage) : rgbImage(inputImage){

}
/***
 *
 */

void JPEGEncoder::encode()
{
    downsampling();
    decomposeBlock8Pixels();
    dct();
    quantization();

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

/***
 *
 * @param matrix
 */

void JPEGEncoder::downsampling(Matrix<> &matrix) {

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
    initMatrix(&yBlocksAfterDCT, yBlocks.size());
    initMatrix(&uBlocksAfterDCT, uBlocks.size());
    initMatrix(&vBlocksAfterDCT, vBlocks.size());
    cout << "8*8 pixels blocks decomposition done." << endl;
}

/***
 *
 * @param in
 * @param out
 */

void JPEGEncoder::decomposeBlock8Pixels(const Matrix<>& in, vector<Matrix<>>& out )
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
                }
            }
            out.push_back(mat);
        }
    }
}

void JPEGEncoder::initMatrix(vector<Matrix<int>>* mat, int size)
{
    mat->resize(size);
    for(int i = 0; i< size; i++)
    {
        mat->at(i).resize(8,8);
    }
}

/***
 *
 * @param blocks
 */

void JPEGEncoder::dct(vector <Matrix<>> &in, vector <Matrix<int>> &out) {

    for(int i = 0; i < in.size(); i++)
    {
        Matrix<int> mat(8, 8);
        DCT::computeDCT(&in[i], &mat);
        out[i] = mat;
    }
}

/**
 *
 */
void JPEGEncoder::dct()
{
    cout << "Computing DCT on YUV..." << endl;
    dct(yBlocks, yBlocksAfterDCT);
    dct(uBlocks, uBlocksAfterDCT);
    dct(vBlocks, vBlocksAfterDCT);
    cout << "DCT applied." << endl;
}
/**
 *
 * @param blocks
 */

void JPEGEncoder::printBlocks(const vector<Matrix<>>& blocks) {
    for(int i =0; i< blocks.size(); i++)
    {
        blocks.at(i).print();
        cout << endl;
    }
}

/**
 *
 */
void JPEGEncoder::printBlocks() {
    printBlocks(yBlocks);
    printBlocks(uBlocks);
    printBlocks(vBlocks);
}

void JPEGEncoder::printBlocksAfterDCT(const vector<Matrix<int>>& blocks) {
    for(int i =0; i< blocks.size(); i++)
    {
        blocks.at(i).printSignedNumber();
        cout << endl;
    }
}

/**
 *
 */
void JPEGEncoder::printBlocksAfterDCT() {
    printBlocksAfterDCT(yBlocksAfterDCT);
    printBlocksAfterDCT(uBlocksAfterDCT);
    printBlocksAfterDCT(vBlocksAfterDCT);
}

void JPEGEncoder::quantization()
{

    quantization(&yBlocksAfterDCT, QuantizationType::LUMINANCE);
    quantization(&uBlocksAfterDCT, QuantizationType::CHROMINANCE);
    quantization(&vBlocksAfterDCT, QuantizationType ::CHROMINANCE);
}

void JPEGEncoder::quantization(vector<Matrix<int>> * mat, QuantizationType type)
{
    DefaultQuantization quant;
    for(int i = 0; i < mat->size(); i++)
    {
        quant.quantizeBlock(mat->at(i), type);
    }
}