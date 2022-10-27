//
// Created by grass on 27/10/2022.
//

#ifndef UNTITLED_INCLUDE_DECLARACION_H_
#define UNTITLED_INCLUDE_DECLARACION_H_

#include <iostream>
#include <utility>
#include <vector>
#include <regex>

// clase para almacenar resultados de la busqueda por regex en codigo fuente de c++ de inicializacion de variables
enum class Tipo {
  tipo_int,
  tipo_double
};

union values {
  int valor_int_;
  double valor_double_;

  explicit values(int valor_int) : valor_int_(valor_int) {}
  explicit values(double valor_double) : valor_double_(valor_double) {}
};

struct Variable {
  std::string nombre_;
  Tipo tipo_;
  values valor_;

  Variable(std::string nombre, Tipo tipo, int valor) : nombre_(std::move(nombre)), tipo_(tipo), valor_(valor) {}
  Variable(std::string nombre, Tipo tipo, double valor) : nombre_(std::move(nombre)), tipo_(tipo), valor_(valor) {}
};

class Declaracion {
 public:

  static Variable getVariable(std::string &line);
  friend std::ostream &operator<<(std::ostream &os, const Declaracion &declaracion);
  explicit Declaracion(std::string &line, int line_number) : variable_(getVariable(line)), line_number_(line_number) {contador_dec++;}

 private:
  const Variable variable_;
  int line_number_;
  static int contador_dec;
};



#endif //UNTITLED_INCLUDE_DECLARACION_H_
