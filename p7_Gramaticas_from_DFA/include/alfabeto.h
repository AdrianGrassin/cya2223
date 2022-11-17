//
// Created by grass on 16/11/2022.
//

#ifndef P7_GRAMATICAS_FROM_DFA_SRC_ALFABETO_H_
#define P7_GRAMATICAS_FROM_DFA_SRC_ALFABETO_H_

#include <set>
#include <iostream>
#include "simbolo.h"

class Alfabeto {
 public:
  Alfabeto(): alfabeto_() {}
  explicit Alfabeto(const std::string& linea);

  void Insertar(const Simbolo& simbolo);

  friend std::ostream& operator<<(std::ostream& os, const Alfabeto& alfabeto);
  bool Pertenece(const Simbolo& simbolo) const;

 private:
  std::set<Simbolo> alfabeto_;
};

#endif //P7_GRAMATICAS_FROM_DFA_SRC_ALFABETO_H_
