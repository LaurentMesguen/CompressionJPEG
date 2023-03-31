//
// Created by FU427LME on 05/03/2023.
//

#include <fstream>
#include <iostream>
#include "../include/Config.h"

Config::Config(string path) : configFilePath(path)
{
    quantificationPace = 0;
    encodingType = eUnknownEncodingType;
}

void Config::load()
{
    ifstream config_file;
    config_file.open(configFilePath);

    if(config_file.fail())
    {
        cerr << "Cannot open the file config.txt" << endl;
        return;
    }

    int temp;

    getline(config_file, this->imageFilename);
    config_file >> quantificationPace;
    config_file >> temp;
    encodingType = (EncodingType) temp;

    config_file.close();
}

/*
void Config::printEncodingType(){

    printf("Codeur : ");
    switch(type_codeur){
        case CODEUR_HUFF_SPI:
            printf("Huffman Statique par image\n");
            break;
        case CODEUR_HUFF_API:
            printf("Huffman Adaptatif par image\n");
            break;
        case CODEUR_HUFF_APB:
            printf("Huffman Adaptatif par bloc\n");
            break;
        case CODEUR_BAC_SPI:
            printf("BAC Statique par image\n");
            break;
        case CODEUR_BAC_SAPI:
            printf("BAC Semi-Adaptatif par image\n");
            break;
        case CODEUR_BAC_API:
            printf("BAC Adaptatif par image\n");
            break;
        default:
            printf("Erreur : type de codeur incorrect\n");
            break;
    }
}*/
