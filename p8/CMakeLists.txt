cmake_minimum_required(VERSION 3.23)
project(p8)

set(CMAKE_CXX_STANDARD 14)

add_executable(p8 main.cpp src/gramatica.cc include/gramatica.h src/simbolo.cc include/simbolo.h)
