cmake_minimum_required(VERSION 3.23)
project(p7_Gramaticas_from_DFA)

set(CMAKE_CXX_STANDARD 17)

add_executable(p7_Gramaticas_from_DFA src/main.cpp src/automata.cc src/alfabeto.cc src/estado.cc src/cadena.cc src/simbolo.cc src/gramatica.cc src/produccion.cc include/produccion.h)
