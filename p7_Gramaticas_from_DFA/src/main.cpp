/**
 * @mainpage PRACTICA 7 - CyA - 2022/2023
 * @section intro_sec Introducción
 *
 * En esta práctica se implementa un programa que a partir de un DFA, construye una gramática regular equivalente.
 *
 * @section install_sec Compilación
 *
 * Para compilar el programa se debe ejecutar el siguiente comando:
 *  - make
 *
 * @section run_sec Ejecución
 *
 * Para ejecutar el programa se debe ejecutar el siguiente comando:
 * - ./dfa2gramar input.fa output.gra
 *         * [input.fa] es el fichero que contiene el DFA
 *         * [output.gra] es el fichero donde se guardará la gramática regular equivalente
 *
 * @section author_sec Autor
 *   @author Adrián Grassin Luis
 *
 * @section license_sec Licencia
 * - Licencia: GNU General Public License v3.0
 *
 * @section bugs_sec Bugs
 * - No se han encontrado bugs
 *
 * @section todo_sec To Do
 * - No hay nada pendiente
 *
 * @section references_sec Referencias
 *   CyA_2022_2023_P7_DFA2Grammar.pdf
 *
 * @section version_sec Version
 *  @version 1.0
 *
 *  @date 16/11/2022
 *
 */


#include <iostream>
#include "../include/gramatica.h"

int main() {
  std::ifstream archivo("automata.fa");
  try {
    if (!archivo.is_open()) {
      throw std::runtime_error("No se pudo abrir el archivo");
    }
    Automata automata(archivo);
    std::cout << automata << std::endl;

    Gramatica gramatica = automata.ConverToGrammar();
    std::cout << gramatica << std::endl;

    std::ofstream archivo_gramatica("gramatica.gra");
    if(!archivo_gramatica.is_open()){
      throw std::runtime_error("No se pudo abrir el archivo");
    }
    gramatica.write(archivo_gramatica);


  } catch (std::runtime_error &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
