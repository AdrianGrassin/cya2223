#ifndef P3__CALC_H_
#define P3__CALC_H_

#include "include/Alfabeto.h"
#include "include/Lenguaje.h"
#include "include/funciones.h"

class Calc {
 public:
    explicit Calc(std::ifstream &file);
   ~Calc() = default;

  void operate();
 private:
  std::vector<std::pair<Alfabeto *, Lenguaje *>> definiciones;
  std::vector<std::pair<std::string, std::string>> operaciones;
    std::vector<std::string> resultados;

};

#endif //P3__CALC_H_
