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
#include <windows.h>

int main(int argc, char *argv[]) {

  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);

  if (argc == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")) {
    std::cout << "HELP - PRACTICA 2 DE CyA \n"
                 "--------------------------\n"
                 "El programa recibira por linea de comandos el nombre del fichero de entrada, el nombre\n"
                 "del fichero de salida y un codigo de operacion: (ejemplo)\n\n"
                 "./p02_strings [filein1.txt] [filein2.txt] [fileout.txt] [opcode]\n"
                 "\n"
                 "OPCODES:\n"
                 "1. Concatenación\n"
                 "2. Intersección\n"
                 "3. Unión\n"
                 "4. Diferencia\n"
                 "5. Inversa\n"
                 "6. Potencia\n"
                 "\n"
                 "La cadena además se generará de la primera forma posible al buscar\n"
                 "las combinaciones de simbolos que coincidan con el alfabeto.\n\n"
                 "End Of Help\n";
    return 0;
  }
  try {
    if (argc == 5) {
      std::ifstream file1(argv[1]);
      std::ifstream file2(argv[2]);
      std::string line;
      std::vector<std::pair<Alfabeto *, Lenguaje *>> list1;
      std::vector<std::pair<Alfabeto *, Lenguaje *>> list2;

      readfile(file1, list1);
      readfile(file2, list2);

      std::cout << "Lenguajes del archivo 1: " << std::endl;
      for (auto a : list1) {
        std::cout << *a.second << "\n";
      }

      std::cout << "\nLenguajes del archivo 2: " << std::endl;
      for (auto a : list2) {
        std::cout << *a.second << "\n";
      }

      std::ofstream fileout(argv[3]);
      int opcode = atoi(argv[4]);
      for (int i = 0; i < list1.size(); i++) { // suponemos que los ficheros de entrada estén siempre bien redactados
        list1[i].second->opcode_menu(fileout, opcode, *list2[i].second);
      }
    } else {
      throw std::runtime_error("No se introdujo un número válido de argumentos ");
    }

  } catch (std::runtime_error &error) {
    std::cerr << error.what();
  }
  return 0;
}
