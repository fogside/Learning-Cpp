cmake_minimum_required(VERSION 3.7)
project(SeminarWorkshop)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp bus.cpp FileNotFoundException.cpp)
add_executable(SeminarWorkshop ${SOURCE_FILES})