cmake_minimum_required(VERSION 3.15)
project(png2asm)

set(CMAKE_CXX_STANDARD 17)

add_executable(png2asm main.cpp lodepng.cpp)