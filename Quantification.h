#ifndef QUANTIFICATION_H_INCLUDED
#define QUANTIFICATION_H_INCLUDED

#include "Image.h"

typedef struct Quant Quant;

struct Quant{
    uint32_t luminance[8][8];
    uint32_t chrominance[8][8];
};
/*
Quant quantification (Image *img, uint32_t qualite);*/

#endif // QUANTIFICATION_H_INCLUDED
