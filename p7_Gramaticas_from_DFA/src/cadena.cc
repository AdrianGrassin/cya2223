//
// Created by grass on 16/11/2022.
//

#include "../include/cadena.h"
/**
 * Constructor de la clase Cadena
 * @param cadena Es una linea que se pasa por referencia y que contiene la cadena
 */

Cadena::Cadena(const std::string &cadena) {
  for (auto &c : cadena) {
    cadena_.emplace_back(std::string(1, c));
  }
}

bool Cadena::operator==(const Cadena &otra_cadena) const {
  return cadena_ == otra_cadena.cadena_;
}

bool Cadena::operator<(const Cadena &otra_cadena) const {
  return cadena_ < otra_cadena.cadena_;
}

std::ostream &operator<<(std::ostream &os, const Cadena &cadena) {
  for (auto &c : cadena.cadena_) {
    os << c;
  }
  return os;
}

uint32_t Cadena::size() const {
  return cadena_.size();
}
std::string Cadena::to_string() const {
    std::string cadena;
    for (auto &c : cadena_) {
        cadena += c.ToString();
    }
    return cadena;
}
