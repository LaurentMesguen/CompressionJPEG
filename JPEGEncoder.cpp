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
    zigZagScan();
    rle();
    huffman();
}

void JPEGEncoder::rle() {
    cout << "RLE encoding..." << endl;
    yRLEVectors = RLE::encode(yVectorsAfterZigZagScan);
    uRLEVectors = RLE::encode(uVectorsAfterZigZagScan);
    vRLEVectors = RLE::encode(vVectorsAfterZigZagScan);
    cout << "RLE encoding finished." << endl;
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

void JPEGEncoder::printVectors(const vector<vector<int>>& vectors) {
    for(int i = 0; i < vectors.size(); i++)
    {
        printVector(vectors.at(i));
    }
}

void JPEGEncoder::printVectors() {

    cout << "Y vectors after zigzag scan:" << endl;
    printVectors(yVectorsAfterZigZagScan);
    cout << "U vectors after zigzag scan:" << endl;
    printVectors(uVectorsAfterZigZagScan);
    cout << "V vectors after zigzag scan:" << endl;
    printVectors(vVectorsAfterZigZagScan);
}

void JPEGEncoder::printVector(const vector<int>& vec) {
    for(int i = 0; i < vec.size(); i++)
    {
        cout << vec.at(i) << " ";
    }
    cout << endl;
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

void JPEGEncoder::zigZagScan()
{
    cout << "ZigZag scan..." << endl;
    zigZagScan(yBlocksAfterDCT, yVectorsAfterZigZagScan);
    zigZagScan(uBlocksAfterDCT, uVectorsAfterZigZagScan);
    zigZagScan(vBlocksAfterDCT, vVectorsAfterZigZagScan);
}

void JPEGEncoder::zigZagScan(const vector<Matrix<int>> &in, vector<vector<int>> &out) {
    for(int i = 0; i < in.size(); i++)
    {
        vector<int> vec = zigZagScan(in.at(i));
        out.push_back(vec);
    }
}

vector<int> JPEGEncoder::zigZagScan(const Matrix<int> &in) {
    vector<int> vec;
    const struct zigZagIndexes {
        int row;
        int col;
    } zigZagIndexes[8*8] =
            {
                    {0, 0},
                    {0, 1}, {1, 0},
                    {2, 0}, {1, 1}, {0, 2},
                    {0, 3}, {1, 2}, {2, 1}, {3, 0},
                    {4, 0}, {3, 1}, {2, 2}, {1, 3}, {0, 4},
                    {0, 5}, {1, 4}, {2, 3}, {3, 2}, {4, 1}, {5, 0},
                    {6, 0}, {5, 1}, {4, 2}, {3, 3}, {2, 4}, {1, 5}, {0, 6},
                    {0, 7}, {1, 6}, {2, 5}, {3, 4}, {4, 3}, {5, 2}, {6, 1}, {7, 0},
                    {7, 1}, {6, 2}, {5, 3}, {4, 4}, {3, 5}, {2, 6}, {1, 7},
                    {2, 7}, {3, 6}, {4, 5}, {5, 4}, {6, 3}, {7, 2},
                    {7, 3}, {6, 4}, {5, 5}, {4, 6}, {3, 7},
                    {4, 7}, {5, 6}, {6, 5}, {7, 4},
                    {7, 5}, {6, 6}, {5, 7},
                    {6, 7}, {7, 6},
                    {7, 7}
            };

    for(int i=0; i<8*8; i++)
        vec.push_back(in.at(zigZagIndexes[i].row, zigZagIndexes[i].col));

    return vec;
}

void JPEGEncoder::printRLEVectors() {
    cout << "Y vectors after RLE:" << endl;
    RLE::print(yRLEVectors);
    cout << "U vectors after RLE:" << endl;
    RLE::print(uRLEVectors);
    cout << "V vectors after RLE:" << endl;
    RLE::print(uRLEVectors);
}

void JPEGEncoder::huffman()
{
    cout << "Huffman encoding..." << endl;
    huffman(yRLEVectors, yHuffmanVectors);
    huffman(uRLEVectors, uHuffmanVectors);
    huffman(vRLEVectors, vHuffmanVectors);
    cout << "Huffman encoding done." << endl;
}


