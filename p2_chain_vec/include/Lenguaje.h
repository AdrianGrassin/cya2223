//
// Created by grass on 06/10/2022.
//

#ifndef P1_SIMBOLTOSTRING_P1_SIMBOLTOSTRING_LENGUAJE_H_
#define P1_SIMBOLTOSTRING_P1_SIMBOLTOSTRING_LENGUAJE_H_

#include "Cadena.h"

class Lenguaje {
 private:
  std::set<Cadena *, compare> cadenas_del_lenguaje;
  Alfabeto *alfabeto_;

 public:
  /**
   * @brief El constructor de la clase Lenguaje toma una std::string por referencia y un puntero a un alfabeto.
   * El proceso es bastante sencillo y se basa en ir añadiendo cada caracter hasta formar una cadena.
   * En caso de ser ' ' el único carácter que conforme una cadena del lenguaje, se reconocerá como lenguaje vacío.
   * Si se toma & como cadena, la tomaremos como cadena vacía y cuando se utilice el método Cadena::get_real_lenght(),
   * retornará su tamaño como 0, en otros casos se retornará el tamaño real de la cadena.
   */
  Lenguaje(const std::string &line, Alfabeto *alfabeto);

  void opcode_menu(std::ofstream &out, int &opcode, Lenguaje &len);

  std::string concatenacion(Lenguaje &len);
  std::string op_union(Lenguaje &len);
  std::string interseccion(Lenguaje &len);
  std::string diferencia(Lenguaje &len);
  std::string inversa();
  std::string potencia();
  std::string subcadenas();

  void print_size_of_chains();
  void concatenates_with(Lenguaje &len);

  friend std::ostream &operator<<(std::ostream &out, Lenguaje &len);

};

#endif //P1_SIMBOLTOSTRING_P1_SIMBOLTOSTRING_LENGUAJE_H_
