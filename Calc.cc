//
// Created by Adri on 13/10/2022.
//

#include "Calc.h"

Calc::Calc(std::ifstream &file) {
  while (!file.eof()) {
    std::string line;
    getline(file, line);
    if (line[3] == '=') {
      auto *dummy_alf = new Alfabeto(alfabetinput(line));
      auto *dummy_cad = new Lenguaje(languajeinput(line), dummy_alf);
      definiciones.emplace_back(dummy_alf, dummy_cad);
    } else {
      operaciones.emplace_back(line.substr(0, line.find_first_of(' ')), line.substr(line.find_first_of(' ') + 1));
    }
  }
}

void Calc::operate() {

   }
