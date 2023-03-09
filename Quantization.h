//
// Created by FU427LME on 09/03/2023.
//

#ifndef JPEGENCODER_QUANTIZATION_H
#define JPEGENCODER_QUANTIZATION_H

#include <cstdint>
#include <cmath>
#include "Matrix.h"

enum QuantizationType {
    LUMINANCE,
    CHROMINANCE
};

class QuantizationMatrix {
public:
    static QuantizationMatrix &instance() {
        static QuantizationMatrix qm;
        return qm;
    }

    const std::vector<std::vector<int>> &getLuminance() const {
        return luminanceMatrix;
    }

    const std::vector<std::vector<int>> &getChrominance() const {
        return chrominanceMatrix;
    }

private:
    QuantizationMatrix() {
        // Quantization matrix for luminance
        luminanceMatrix = {{16, 11, 10, 16, 24,  40,  51,  61},
                           {12, 12, 14, 19, 26,  58,  60,  55},
                           {14, 13, 16, 24, 40,  57,  69,  56},
                           {14, 17, 22, 29, 51,  87,  80,  62},
                           {18, 22, 37, 56, 68,  109, 103, 77},
                           {24, 35, 55, 64, 81,  104, 113, 92},
                           {49, 64, 78, 87, 103, 121, 120, 101},
                           {72, 92, 95, 98, 112, 100, 103, 99}};

        // Quantization matrix for chrominance
        chrominanceMatrix = {{17, 18, 24, 47, 99, 99, 99, 99},
                        {18, 21, 26, 66, 99, 99, 99, 99},
                        {24, 26, 56, 99, 99, 99, 99, 99},
                        {47, 66, 99, 99, 99, 99, 99, 99},
                        {99, 99, 99, 99, 99, 99, 99, 99},
                        {99, 99, 99, 99, 99, 99, 99, 99},
                        {99, 99, 99, 99, 99, 99, 99, 99},
                        {99, 99, 99, 99, 99, 99, 99, 99}};
    }

    vector<vector<int>> luminanceMatrix;
    vector<vector<int>> chrominanceMatrix;
};

// Strategy design pattern pour l'algorithme de quantification
class QuantizationAlgorithm {
public:
    virtual ~QuantizationAlgorithm() = default;

    virtual void quantizeBlock(Matrix<int> &block, QuantizationType type) = 0;
};

class DefaultQuantization : public QuantizationAlgorithm {
public:
    void quantizeBlock(Matrix<int> &block, QuantizationType type) override {

        const auto &qm = type == LUMINANCE ? QuantizationMatrix::instance().getLuminance() : QuantizationMatrix::instance().getChrominance();

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                block.setPixel(i, j , round(block.at(i,j) / static_cast<float>(qm[i][j])));
            }
        }
    }
};


#endif //JPEGENCODER_QUANTIZATION_H
