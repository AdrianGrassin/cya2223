#ifndef UNTITLED_INCLUDE_ANALIZER_H_
#define UNTITLED_INCLUDE_ANALIZER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

#include "declaracion.h"
#include "comentarios.h"
#include "bucles.h"


// clase que lee el fichero y crea objetos de tipo Declaraciones

class analizer {
 public:
  explicit analizer(std::ifstream &file);

  friend std::ostream &operator<<(std::ostream &os, const analizer &analizer);
 private:

  bool main_found_ = false;
  std::vector<comentarios> comentarios_;
  std::vector<Declaracion> declaraciones_;
  std::vector<bucles> bucles_;

};

#endif //UNTITLED_INCLUDE_ANALIZER_H_
