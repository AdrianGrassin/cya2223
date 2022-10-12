/**
 * @file Simbolo.cc
 * @brief Simbolo que es representado con un std::string
 */


#include "../include/Simbolo.h"

Simbolo::Simbolo(const std::string& simbol) {
  if (simbol == " ") {
    simbolo_ = CADENA_VACIA;
  } else {
    simbolo_ = simbol;
  }
}

bool Simbolo::operator<(const Simbolo& otrosimbolo) const {
  if (simbolo_ == CADENA_VACIA) {
    return true;
  }
  return simbolo_ < otrosimbolo.simbolo_;
}

bool Simbolo::operator==(const Simbolo& otrosimbolo) const {
  return simbolo_ == otrosimbolo.simbolo_;
}

Simbolo::Simbolo() {
  simbolo_ = ' ';
}

std::ostream &operator<<(std::ostream &out, Simbolo &s) {
  out << s.simbolo_;
  return out;
}

Simbolo::Simbolo(const char &simbol) {
  simbolo_ = std::string (1, simbol);
}

void Simbolo::operator+=(const char& caracter) {
  simbolo_ += caracter;
}



