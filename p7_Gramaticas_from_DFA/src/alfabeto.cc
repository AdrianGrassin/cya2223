//
// Created by grass on 16/11/2022.
//

#include "../include/alfabeto.h"

/*
 * Constructor de la clase Alfabeto
 *   - Recibe una string de la forma: "a b c d 0 1 2"
 *   - Convierte cada caracter en un simbolo
 *   - Los simbolos se almacenan en un set
 */
Alfabeto::Alfabeto(const std::string &linea) {
  for (auto &i : linea) {
    if (i != ' ') {
      alfabeto_.insert(Simbolo(std::string(1, i)));
    }
  }
}

/*
 * Sobrecarga del operador <<
 */
std::ostream &operator<<(std::ostream &os, const Alfabeto &alfabeto) {
  for (auto &i : alfabeto.alfabeto_) {
    os << i << " ";
  }
  return os;
}

/*
 * Verifica si un simbolo Pertenece al alfabeto
 */
bool Alfabeto::Pertenece(const Simbolo &simbolo) const {
  return alfabeto_.find(simbolo) != alfabeto_.end();
}
void Alfabeto::Insertar(const Simbolo &simbolo) {
  alfabeto_.insert(simbolo);
}
