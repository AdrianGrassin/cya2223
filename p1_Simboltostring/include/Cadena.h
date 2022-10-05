//
// Created by grass on 01/10/2022.
//

#ifndef CYA3_P1_CADENA_H_
#define CYA3_P1_CADENA_H_

#include "Alfabeto.h"
#include "Simbolo.h"
#include <iostream>
#include <fstream>
/**
 * @class Cadena
 * @brief Esta clase contiene 3 atributos privados:
 *  - longitud. (indica la longitud de la cadena).
 *  - Un puntero a su alfabeto. (Para determinar el alfabeto de la cadena).
 *  - Un puntero a una cadena de Símbolos. (Este puntero mantiene la dirección inicial de la cadena).
 *      Se podrá acceder a todos los Símbolos de la cadena sabiendo la longitud y dirección inicial de la misma.
 */
class Cadena {
 private:
  int longitud;
  Alfabeto *alfabeto;
  Simbolo *cadena_;

 public:
  Cadena(const std::string &linea, Alfabeto *alfabeto_de_la_cadena);
  ~Cadena();

  // Funciones de retorno

  /**
   * @return Esta función retorna la longitud de la cadena
   */
  int get_longitud() const { return longitud; };

  /**
   * @return Esta función retorná un puntero a un vector de símbolos que equivaldrá a la cadena, en caso de que no se pueda formar la cadena será "error, cadena no soportada";
   */
  void set_string(std::string &cadena);

  /**
   * @return Esta función retorna la cadena invertida como un string
   */
  std::string inversa();

  /**
   * @return Esta función retorna un string con todos los prefijos posibles
   */
  std::string prefijos();

  /**
   * @return Esta función retorna un string con todos los sufijos posibles
   */
  std::string sufijos();

  /**
   * @return Esta función retorna un string con todas las subcadenas posibles
   */
  std::string subcadenas();

  /**
   *
   * @param cadena
   * @param maxsize
   * @param posicion
   * @param size
   * @param solucion
   * @return retorna true si se puede formar la cadena dada con el alfabeto dado y false en otro caso
   * @brief Esta función recursiva busca una posible solución para determinar que símbolos componen la cadena
   * que nos han dado. Empezará en la posición 0 de la cadena e irá buscando si en el alfabeto coincide alguno
   * de los simbolos de tamaño (size). En caso de encontrar se vuelve a llamar a sí misma y en caso de no encontrar
   * se incrementa el size para comprobar si es posible que haya un simbolo de tamaño mayor por encontrar.
   */
  bool comprobar_cadena(const std::string& cadena,const int& maxsize, int posicion, int size, std::vector<std::string> &solucion);

  /**
   * @brief Esta función servirá de menú interno del programa a la hora de determinar que función usar dependiendo del opcode introducido
   */
  void opcode_menu(std::ofstream &fileout, int selec);


  void print_cadena();

};

#endif // CYA3_P1_CADENA_H_
