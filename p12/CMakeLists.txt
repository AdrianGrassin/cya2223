cmake_minimum_required(VERSION 3.23)
project(p12)

set(CMAKE_CXX_STANDARD 14)

add_executable(p12 main.cpp include/utilities.h source/utilities.cc include/BigInt.h source/BigInt.cc)
