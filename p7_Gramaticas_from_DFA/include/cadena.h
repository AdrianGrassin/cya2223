//
// Created by grass on 16/11/2022.
//

#ifndef P7_GRAMATICAS_FROM_DFA_INCLUDE_CADENA_H_
#define P7_GRAMATICAS_FROM_DFA_INCLUDE_CADENA_H_

#include <vector>
#include "simbolo.h"

class Cadena {
 public:
  Cadena() = default;
  explicit Cadena(const std::string &cadena);

  std::string to_string() const;
  uint32_t size() const;

  bool operator==(const Cadena &otra_cadena) const;
  bool operator<(const Cadena &otra_cadena) const;

  // iterable
  typedef std::vector<Simbolo>::iterator iterator;
  typedef std::vector<Simbolo>::const_iterator const_iterator;

  iterator begin() { return cadena_.begin(); }
  iterator end() { return cadena_.end(); }
  const_iterator begin() const { return cadena_.begin(); }
  const_iterator end() const { return cadena_.end(); }




  friend std::ostream &operator<<(std::ostream &os, const Cadena &cadena);
 private:
  std::vector<Simbolo> cadena_;

};

#endif //P7_GRAMATICAS_FROM_DFA_INCLUDE_CADENA_H_
