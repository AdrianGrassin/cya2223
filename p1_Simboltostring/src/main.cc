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
#include "../include/Cadena.h "
#include <windows.h>

int main(int argc, char *argv[]) {

  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);

  if (argc == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")) {
    std::cout << "HELP - PRACTICA 1 DE CyA \n"
                 "--------------------------\n"
                 "El programa recibira por linea de comandos el nombre del fichero de entrada, el nombre\n"
                 "del fichero de salida y un codigo de operacion: (ejemplo)\n\n"
                 "./p01_strings [filein.txt] [fileout.txt] [opcode]\n"
                 "\n"
                 "OPCODES:\n"
                 "1. Longitud\n"
                 "2. Inversa\n"
                 "3. Prefijos\n"
                 "4. Sufijos\n"
                 "5. Subcadenas\n"
                 "\n"
                 "End Of Help\n";
    return 0;
  }
  try {
    if (argc == 4) {
      std::ifstream file(argv[1]);
      std::string line;
      std::vector<std::pair<Alfabeto *, Cadena *>> proglist;

      if (file.is_open()) {
        while (getline(file, line)) {
          auto *dummy_alf = new Alfabeto(line);
          auto *dummy_cad = new Cadena(line, dummy_alf);
          proglist.emplace_back(dummy_alf, dummy_cad);
        }

        for (auto a : proglist) {
          a.second->print_cadena();
        }

      } else {
        throw std::runtime_error("El archivo no se encontró o no se pudo abrir");
      }

      std::ofstream outputfile(argv[2]);
      int opcode = atoi(argv[3]);
      for (auto a : proglist) {
        a.second->opcode_menu(outputfile, opcode);
      }

    } else {
      throw std::runtime_error("No se introdujo un número válido de argumentos ");
    }
  } catch (std::runtime_error &error) {
    std::cerr << error.what();
  }
  return 0;
}
