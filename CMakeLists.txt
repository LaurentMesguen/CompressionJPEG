cmake_minimum_required(VERSION 3.23)
project(JPEGEncoder)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(JPEGEncoder SHARED ${SOURCES})

target_include_directories(JPEGEncoder PUBLIC include PRIVATE src)
