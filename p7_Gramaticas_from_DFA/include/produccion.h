//
// Created by grass on 17/11/2022.
//

#ifndef P7_GRAMATICAS_FROM_DFA_SRC_PRODUCCIONES_H_
#define P7_GRAMATICAS_FROM_DFA_SRC_PRODUCCIONES_H_

#include <vector>
#include "estado.h"

class Produccion {
 public:
  Produccion(const Estado &estado, const Alfabeto &alfabeto);
  Produccion(std::string &linea, const Alfabeto &alfabeto);

  static std::string EstadoToString(const Estado &estado);

  friend std::ostream &operator<<(std::ostream &os, const Produccion &produccion);

 private:
  Simbolo no_terminal_;
  std::vector<std::string> produccion_;
  Alfabeto alfabeto_;

};

#endif //P7_GRAMATICAS_FROM_DFA_SRC_PRODUCCIONES_H_
