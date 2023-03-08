#include <stdio.h>
#include <stdlib.h>

#define CODEUR_HUFF_SPI 0 // huffman statique par image
#define CODEUR_HUFF_API 1 // huffman adaptatif par image
#define CODEUR_HUFF_APB 2 // huffman adaptatif par bloc
#define CODEUR_BAC_SPI 3 // BAC statique par image
#define CODEUR_BAC_SAPI 4 // BAC semi_adaptatif
#define CODEUR_BAC_API 5 // BAC adaptatif par image


/*#include "conversionRGB_YUV.h"
#include "conversionYUV_RGB.h"
#include "downsampling.h"
#include "dct.h"
#include "quantification.h"
#include "dequantification.h"
#include "zigzag.h"
#include "dpcm.h"
#include "izigzag.h"
#include "idct.h"
#include "affichage.h"
#include "creation_config_file.h"
#include "idpcm.h"*/
/*#include "psnr.h"
#include "codeur_arithmetique.h"
#include "huffman_statique.h"
#include "huffman_adaptatif.h"
#include "writeImg.h"*/
#include "Config.h"
#include "Image.h"
#include "JPEGEncoder.h"
#include <string>
#include <fstream>
#include <iostream>
//#include "Quantification.h"

using namespace std;

int main (int argc, char* argv[]) {

    string root_path = "..\\";

    /** Read config file **/
    Config config( root_path + "config.ini");
    config.load();
    /********************************/

    // Get input BMP image
    Image inputImage;
    inputImage.readFromFile(root_path + "img\\lena256.bmp");
    //inputImage.printRGB();
    //inputImage.printYUV();

    /** Compression **/
    JPEGEncoder encoder(&inputImage);
    encoder.encode();
    //inputImage.printYUV();
    //encoder.printBlocks();
    /*img = dct(img);
    table = quantification(img, pas_quantification);
    ImageVector *imgV = zigzag(img);
    dpcm(imgV);
    imgRle = rle(imgV);

    if(type_codeur == CODEUR_BAC_SPI || type_codeur == CODEUR_BAC_API || type_codeur == CODEUR_BAC_SAPI){
        imgBAC = BAC_ImageRle(imgRle, type_codeur);
    }
    else if(type_codeur == CODEUR_HUFF_API)
        imgCode = tables_Code(imgRle);

    taille_config_file_sortie = creation_config_file(imgRle, imgBAC, imgCode, table, largeur, hauteur, type_codeur);*/

    /** Decompression **/
    /*imgV = irle(imgRle);
    idpcm(imgV);
    img = izigzag(imgV);
    dequantification(img, pas_quantification);
    img = idct(img);
    Image *img_dest = conversionYUV_RGB(img);

    // Création du config_file de sortie imgO.txt contenant les matrices RGB
    writeImg(img);

    taux = calcul_taux(taille_config_file_entree, taille_config_file_sortie);
    resultat_psnr = psnr(img_source, img_dest);
    bpp = calcul_bpp(largeur*hauteur, taille_config_file_sortie);

    /** Ecriture du fichier out.txt **/
    /*FILE *out = fopen("out.txt", "w");

    /*********************************/

    cout << endl << "Program finished" << endl << endl;

    return EXIT_SUCCESS;
}
