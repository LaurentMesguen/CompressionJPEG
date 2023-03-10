cmake_minimum_required(VERSION 3.23)
project(JPEGEncoder)

set(CMAKE_CXX_STANDARD 23)

add_executable(JPEGEncoder main.cpp
        Config.cpp Config.h
        Image.cpp Image.h
        JPEGEncoder.cpp JPEGEncoder.h
        Matrix.cpp Matrix.h
        DCT.cpp DCT.h
        Quantization.h
        RLE.cpp RLE.h
        Huffman.cpp Huffman.h
        EncodingStrategy.cpp EncodingStrategy.h)
