//
// Created by grass on 16/11/2022.
//

#ifndef P7_GRAMATICAS_FROM_DFA_SRC_ESTADO_H_
#define P7_GRAMATICAS_FROM_DFA_SRC_ESTADO_H_

#include <iostream>
#include <vector>
#include <sstream>
#include "simbolo.h"
#include "alfabeto.h"

class Estado {
 public:
  Estado() = default;
  explicit Estado(const std::string &estado, std::vector<Estado> &vector_estados, Alfabeto &alfabeto);
  std::string to_string() const;

  int get_id() const;
  Estado *transicion(const Simbolo &simbolo);
  std::vector<std::pair<Simbolo, Estado *>> get_transiciones() const;

  bool es_aceptacion() const;
  friend std::ostream &operator<<(std::ostream &os, const Estado &estado);

 private:
  int estado_;
  bool aceptacion_;
  std::vector<std::pair<Simbolo, Estado *>> transiciones_;

};

#endif //P7_GRAMATICAS_FROM_DFA_SRC_ESTADO_H_
