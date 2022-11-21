//
// Created by grass on 17/11/2022.
//

#ifndef P7_GRAMATICAS_FROM_DFA_INCLUDE_GRAMATICA_H_
#define P7_GRAMATICAS_FROM_DFA_INCLUDE_GRAMATICA_H_

class Automata;

#include "automata.h"
#include "produccion.h"


class Gramatica {
 public:
  explicit Gramatica(const Automata &dfa);
  explicit Gramatica(std::ifstream &archivo);

  void write(std::ofstream &os) const;
  friend std::ostream &operator<<(std::ostream &os, const Gramatica &gramatica);

 private:
  Alfabeto alfabeto_;
  Simbolo simbolo_inicial_;
  std::vector<Simbolo> no_terminales_;
  std::vector<Produccion> producciones_;

};

#endif //P7_GRAMATICAS_FROM_DFA_INCLUDE_GRAMATICA_H_
