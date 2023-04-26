cmake_minimum_required(VERSION 3.0)
project(algrithmHW)

set(CMAKE_CXX_STANDARD 11)
#FILE(GLOB SC_FILES "*.cpp" "*.h")
set(SOURCE_FILES main.cpp HuffmanTree.h HuffmanTree.cpp  BitStream.cpp BitStream.hpp)
add_executable(algrithmHW ${SOURCE_FILES})
