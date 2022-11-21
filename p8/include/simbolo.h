//
// Created by grass on 21/11/2022.
//

#ifndef P8_SRC_SIMBOLO_H_
#define P8_SRC_SIMBOLO_H_

#include <string>

class Simbolo {

 public:
    explicit Simbolo(const std::string& simbol);
    Simbolo() = default;
    ~Simbolo() = default;

    bool operator==(const Simbolo& otro_simbolo) const;
    bool operator<(const Simbolo& otro_simbolo) const;
    bool operator!=(const Simbolo& otro_simbolo) const;

    friend std::istream& operator>>(std::istream& is, Simbolo& simbolo) {
        is >> simbolo.simbolo_;
        return is;
    }

    std::string ToString() const;

 private:
   std::string simbolo_;

};

#endif //P8_SRC_SIMBOLO_H_
