//
// Created by grass on 16/11/2022.
//

#ifndef P7_GRAMATICAS_FROM_DFA_SRC_SIMBOLO_H_
#define P7_GRAMATICAS_FROM_DFA_SRC_SIMBOLO_H_

#include <iostream>

class Simbolo {
 public:
  Simbolo() = default;
  explicit Simbolo(const std::string &simbolo);

  bool operator==(const Simbolo &otro_simbolo) const;
  bool operator<(const Simbolo &otro_simbolo) const;
  bool operator!=(const Simbolo &otro_simbolo) const;

  std::string ToString() const;

  friend std::ostream &operator<<(std::ostream &os, const Simbolo &simbolo);

 private:
  std::string simbolo_;
};

#endif //P7_GRAMATICAS_FROM_DFA_SRC_SIMBOLO_H_
