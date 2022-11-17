//
// Created by grass on 16/11/2022.
//

#include <utility>

#include "../include/simbolo.h"

/*
 * Constructor de la clase Simbolo
 */
Simbolo::Simbolo(const std::string &simbolo) {
  simbolo_ = simbolo;
}

/*
 * Sobrecarga del operador ==
 */
bool Simbolo::operator==(const Simbolo &simbolo) const {
  return simbolo_ == simbolo.simbolo_;
}

/*
 * Sobrecarga del operador <
 */
bool Simbolo::operator<(const Simbolo &simbolo) const {
  return simbolo_ < simbolo.simbolo_;
}

/*
 * Sobrecarga del operador <<
 */
std::ostream &operator<<(std::ostream &os, const Simbolo &simbolo) {
  os << simbolo.simbolo_;
  return os;
}

bool Simbolo::operator!=(const Simbolo &otro_simbolo) const {
    return simbolo_ != otro_simbolo.simbolo_;
}
std::string Simbolo::ToString() const {
  return simbolo_;
}


