//
// Created by grass on 09/10/2022.
//

#ifndef P1_SIMBOLTOSTRING_P1_SIMBOLTOSTRING_INCLUDE_FUNCIONES_H_
#define P1_SIMBOLTOSTRING_P1_SIMBOLTOSTRING_INCLUDE_FUNCIONES_H_

#include <vector>
#include <utility>
#include <fstream>
#include "Alfabeto.h"
#include "Lenguaje.h"


void readfile(std::ifstream& file, std::vector<std::pair<Alfabeto *, Lenguaje *>>& lista);
std::string languajeinput(std::string& line);
std::string alfabetinput(std::string& line);

#endif //P1_SIMBOLTOSTRING_P1_SIMBOLTOSTRING_INCLUDE_FUNCIONES_H_
