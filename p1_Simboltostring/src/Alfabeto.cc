/**
 * @file Alfabeto.cc
 * @brief Contiene la definición una clase alfabeto bastante simple.
 *
 */



#include "../include/Alfabeto.h"

Alfabeto::Alfabeto(const std::string &linea) {  //string input has to be like:a b c d
  bool delimitador = false;
  std::string alfabetostring(linea.substr(0, linea.find_last_of(' ') + 1));
  std::string buffer;
  for (const auto& a : alfabetostring) {
    if (a == ' ' && a != *linea.begin()) {
      delimitador = true;
    }
    if (delimitador) {
      alfabeto_.insert(Simbolo(buffer));
      buffer.clear();
      delimitador = false;
      continue;
    }

    buffer += a;
  }

  if(alfabeto_.empty()){
    for (const auto& a : linea){
      alfabeto_.insert(Simbolo(a));
    }
  }
}
std::set<Simbolo> Alfabeto::getAlfabeto() const {
  return alfabeto_;
}
