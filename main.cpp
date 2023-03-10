#include <stdlib.h>

#define CODEUR_HUFF_SPI 0 // huffman statique par image
#define CODEUR_HUFF_API 1 // huffman adaptatif par image
#define CODEUR_HUFF_APB 2 // huffman adaptatif par bloc
#define CODEUR_BAC_SPI 3 // BAC statique par image
#define CODEUR_BAC_SAPI 4 // BAC semi_adaptatif
#define CODEUR_BAC_API 5 // BAC adaptatif par image

#include "Config.h"
#include "Image.h"
#include "JPEGEncoder.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main (int argc, char* argv[]) {

    string root_path = "..\\";

    /** Read config file **/
    Config config( root_path + "config.ini");
    config.load();
    /********************************/

    // Get input BMP image
    Image inputImage;
    inputImage.readFromFile(root_path + "img\\damier8.bmp");
    inputImage.printRGB();

    /** Compression **/
    JPEGEncoder encoder(&inputImage);
    encoder.encode();
    //encoder.printBlocks();
    encoder.printBlocksAfterDCT();
    encoder.printVectors();

    /** Decompression **/


    /*********************************/

    cout << endl << "Program finished" << endl << endl;




    return EXIT_SUCCESS;
}
