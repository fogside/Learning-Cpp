cmake_minimum_required(VERSION 3.6)
project(first)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES figures.cpp figures.h)
add_executable(first ${SOURCE_FILES})