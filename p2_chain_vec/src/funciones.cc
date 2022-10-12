//
// Created by grass on 09/10/2022.
//

#include "../include/funciones.h"

void readfile(std::ifstream &file, std::vector<std::pair<Alfabeto *, Lenguaje *>> &lista) {
  std::string line;
  if (file.is_open()) {
    while (getline(file, line)) {
      auto *dummy_alf = new Alfabeto(alfabetinput(line));
      auto *dummy_cad = new Lenguaje(languajeinput(line), dummy_alf);
      lista.emplace_back(dummy_alf, dummy_cad);
    }
  } else {
    throw std::runtime_error("El primer archivo no se encontró o no se pudo abrir");
  }
}

std::string alfabetinput(std::string &line) {
  return line.substr(line.find_first_of('{') + 2, line.find_first_of('}') - 2);
}

std::string languajeinput(std::string &line) {
  std::string newline = line.substr(2);
  newline = newline.substr(newline.find_first_of('{') + 2);
  return newline.substr(0, newline.size() - 1);
}


