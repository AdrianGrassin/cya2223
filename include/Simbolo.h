//
// Created by grass on 01/10/2022.
//

#ifndef CYA3_P1_INCLUDE_SIMBOLO_H_
#define CYA3_P1_INCLUDE_SIMBOLO_H_

#define CADENA_VACIA "&"
#include <vector>
#include <string>
#include <iostream>

class Simbolo {
 private:
  std::string simbolo_;
 public:
  Simbolo();
  explicit Simbolo(const std::string& simbol);
  explicit Simbolo(const char& simbol);
  inline std::string getsimbolo() const {return simbolo_;};
  inline int get_simbolsize() const {return simbolo_.size();};

  bool operator<(const Simbolo& otrosimbolo) const;
  bool operator==(const Simbolo& otrosimbolo) const;
  void operator+=(const char& caracter);
  friend std::ostream &operator<<(std::ostream &out, Simbolo &s);

};
#endif // CYA3_P1_INCLUDE_SIMBOLO_H_
