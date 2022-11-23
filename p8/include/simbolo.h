#ifndef P8_SRC_SIMBOLO_H_
#define P8_SRC_SIMBOLO_H_

#include <string>

class Simbolo {

 public:
  explicit Simbolo(const std::string &simbol);
  Simbolo() = default;
  ~Simbolo() = default;


  bool EsTerminalUnitario() const;
  bool EsNoTerminalFNC() const;

  bool operator==(const Simbolo &otro_simbolo) const;
  bool operator<(const Simbolo &otro_simbolo) const;
  bool operator!=(const Simbolo &otro_simbolo) const;

  friend std::istream &operator>>(std::istream &is, Simbolo &simbolo);

  // make simbol iterable
  std::string::iterator begin() { return simbolo_.begin(); }
  std::string::iterator end() { return simbolo_.end(); }
  std::string::const_iterator begin() const { return simbolo_.begin(); }
  std::string::const_iterator end() const { return simbolo_.end(); }

  std::string ToString() const;
  static Simbolo GetNewNonTerminal();

  Simbolo &operator+(const Simbolo &otro_simbolo);

 private:
  std::string simbolo_;

};

#endif //P8_SRC_SIMBOLO_H_
