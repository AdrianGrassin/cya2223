//
// Created by grass on 21/11/2022.
//

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
  explicit Gramatica(std::ifstream& archivo);
  ~Gramatica() = default;

  std::vector<Simbolo> GetProduccion(const Simbolo& simbolo) const;
  bool ProduccionVacia(const Simbolo& simbolo) const;
  bool ProduccionUnitaria(const Simbolo& simbolo) const;

  Gramatica ToChomsky() const;
  void EscribirGramatica(std::ofstream& archivo) const;



 private:
  std::map<Simbolo, std::vector<Simbolo>> producciones_;
  Simbolo simbolo_inicial_;
  std::set<Simbolo> simbolos_no_terminales_;
  std::set<Simbolo> simbolos_terminales_;

};

#endif //P8_SRC_GRAMATICA_H_
