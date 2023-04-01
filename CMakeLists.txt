cmake_minimum_required(VERSION 3.23)
project(JPEGEncoder)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(JPEGEncoder SHARED ${SOURCES})

target_include_directories(JPEGEncoder
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        src
        )

# installation rules
include(GNUInstallDirs)
install(TARGETS JPEGEncoder
        EXPORT JPEGEncoderTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT JPEGEncoderTargets
        FILE JPEGEncoderConfig.cmake
        NAMESPACE JPEGEncoder::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/JPEGEncoder
        )
