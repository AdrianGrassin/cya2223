#ifndef P8_SRC_GRAMATICA_H_
#define P8_SRC_GRAMATICA_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include "simbolo.h"

class Gramatica {
 public:
  explicit Gramatica(std::ifstream &archivo);
  ~Gramatica() = default;



  Gramatica ToChomsky() const;
  void EscribirGramatica(std::basic_ostream<char> &archivo) const;
  friend std::ostream &operator<<(std::ostream &os, const Gramatica &gramatica);

 private:
  std::map<Simbolo, std::vector<Simbolo>> producciones_;
  Simbolo simbolo_inicial_;
  std::set<Simbolo> simbolos_no_terminales_;
  std::set<Simbolo> simbolos_terminales_;

};

#endif //P8_SRC_GRAMATICA_H_
