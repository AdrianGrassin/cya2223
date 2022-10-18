/**
 * @mainpage [Universidad de La Laguna]
 * Escuela Superior de Ingeniería y Tecnología
 * -------------------------------------------
 * Computabilidad y Algoritmia
 * -----------------------------------------
 * Correo: alu0101349480@ull.edu.es
 *
 *  Práctica #01: Símbolos, alfabetos y cadenas
 *  --------------------------------------------
 *  En esta práctica 1 se usan las clases de Cadena, Simbolo y Alfabeto.
 *
 * GitHub
 * ------
 * \ref https://github.com/AdrianGrassin/CyA/tree/master    (privado)
 * @version 1.0
 * @date 1/10/2022
 * @author Adrian Grassin Luis
 *
 * @file main.cc
 * @brief Main bastante sencillo.
 */

#include <iostream>
#include "../include/Alfabeto.h"
#include "../include/Lenguaje.h"
#include "../include/funciones.h"
#include "../Calc.h"
// #include <windows.h>

int main(int argc, char *argv[]) {

 // SetConsoleCP(CP_UTF8);
 //  SetConsoleOutputCP(CP_UTF8);

  if (argc == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")) {
    std::cout << "HELP - PRACTICA 3 DE CyA \n";
    return 0;
  }
  try {
    if (argc == 2) {
      std::ifstream file1(argv[1]);
      if(file1.is_open()){
        Calc C(file1);
        C.operate();
        std::cout << "El resultado de las operaciones es: " << std::endl;
        C.get_resultado();
        std::cout << std::endl;

      } else {
        throw std::invalid_argument("Error: El fichero no existe");
      }

    } else {
      throw std::runtime_error("No se introdujo un número válido de argumentos ");
    }

  } catch (std::runtime_error &error) {
    std::cerr << error.what();
  }
  return 0;
}
