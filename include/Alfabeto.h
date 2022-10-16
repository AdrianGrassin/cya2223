#ifndef CYA3_P1_ALFABETO_H_
#define CYA3_P1_ALFABETO_H_

#include "Simbolo.h"
#include <set>

class Alfabeto {
 private:
  std::set<Simbolo> alfabeto_;

 public:
  explicit Alfabeto(const std::string& linea);
  std::set<Simbolo> getAlfabeto() const;


  Alfabeto operator+(const Alfabeto& a) const;

};

#endif // CYA3_P1_ALFABETO_H_
