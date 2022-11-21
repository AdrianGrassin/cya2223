//
// Created by grass on 21/11/2022.
//

#include "../include/simbolo.h"
Simbolo::Simbolo(const std::string &simbol) {
  simbolo_ = simbol;
}

bool Simbolo::operator==(const Simbolo &otro_simbolo) const {
  return simbolo_ == otro_simbolo.simbolo_;
}

bool Simbolo::operator<(const Simbolo &otro_simbolo) const {
  return simbolo_ < otro_simbolo.simbolo_;
}

bool Simbolo::operator!=(const Simbolo &otro_simbolo) const {
  return simbolo_ != otro_simbolo.simbolo_;
}

std::string Simbolo::ToString() const {
  return simbolo_;
}

