//
// Created by grass on 27/10/2022.
//

#ifndef UNTITLED__BUCLES_H_
#define UNTITLED__BUCLES_H_

#include <iostream>

class bucles {

 public:
    explicit bucles(std::string &line, int line_number);
    friend std::ostream &operator<<(std::ostream &os, const bucles &bucles);

 private:
  std::string tipo_bucle_;
  int line_number_;
  static int contador_buc;
};




#endif //UNTITLED__BUCLES_H_
