//
// Created by grass on 21/11/2022.
//

#include "../include/simbolo.h"

static int simbolo_count = 0;

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

bool Simbolo::EsTerminalUnitario() const {
  if (simbolo_.size() > 1) {
    return false;
  }

  if (std::isupper(*simbolo_.c_str())) {
    return false;
  }
  return true;
}

bool Simbolo::EsNoTerminalFNC() const {
  if (simbolo_.size() > 2) {
    return false;
  }

  for (auto c : simbolo_) {
    if (!std::islower(c)) {
      return false;
    }
  }
  return true;
}

bool Simbolo::EsNoTerminalUnitario() const {
  if (simbolo_.size() > 1) {
    return false;
  }

  if (std::islower(*simbolo_.c_str())) {
    return false;
  }

  return true;
}

Simbolo Simbolo::GetNewNonTerminal() {
  return Simbolo( std::string(1, 'F' + simbolo_count++));
}
Simbolo &Simbolo::operator+(const Simbolo &otro_simbolo) {
  simbolo_ += otro_simbolo.simbolo_;
  return *this;
}

