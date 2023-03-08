cmake_minimum_required(VERSION 3.23)
project(CompressionJPEGcpp)

set(CMAKE_CXX_STANDARD 23)

add_executable(CompressionJPEGcpp main.cpp Config.cpp Config.h Image.cpp Image.h Quantification.cpp Quantification.h JPEGEncoder.cpp JPEGEncoder.h Matrix.cpp Matrix.h)
