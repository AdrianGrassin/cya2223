/**
 * @mainpage PRACTICA 8 - CyA - 2022/2023
 * @section intro_sec Introducción
 *
 * En esta práctica se implementa un programa que a partir de una gramática, construye una gramática en forma normal de
 * Chomsky equivalente.
 *
 * @section install_sec Compilación
 *
 * Para compilar el programa se debe ejecutar el siguiente comando:
 *  - make
 *
 * @section run_sec Ejecución
 *
 * Para ejecutar el programa se debe ejecutar el siguiente comando:
 * - ./Gramar2CNF input.fa output.gra
 *         * [input.gra] es el fichero que contiene la gramática.
 *         * [output.gra] es el fichero donde se guardará la gramática en forma normal de Chomsky equivalente.
 *
 * @section author_sec Autor
 *   @author Adrián Grassin Luis
 *
 * @section license_sec Licencia
 * - Licencia: GNU General Public License v3.0
 *
 * @section bugs_sec Bugs
 * - No se han encontrado bugs.
 *
 * @section todo_sec To Do
 * - No hay nada pendiente.
 *
 * @section references_sec Referencias
 *   CyA_2022_2023_P8_Grammar2CNF.pdf
 *
 * @section version_sec Version
 * @version 1.0
 *
 * @date 20/11/2022
 *
 */


#include <iostream>
#include "../include/gramatica.h"

int main(int argc, char *argv[]) {

  // Argument Handling
  if (std::string(argv[1]) == "--help") {
    std::cout << "Uso: ./Grammar2CNF input.gra output.gra" << std::endl;
    std::cout << "Convierte una gramática en una gramática equivalente escrita en forma normal de Chomsky" << std::endl;
    std::cout << "input.gra: Fichero que contiene la Gramática introducida" << std::endl;
    std::cout << "output.gra: Fichero donde se guardará la gramática en forma normal de Chomsky equivalente"
              << std::endl;
    return 0;
  }

  if (argc != 3) {
    std::cerr << "Error: Numero de argumentos incorrecto" << std::endl;
    std::cerr << "Uso: ./dfa2gramar input.fa output.gra" << std::endl;
    std::cerr << "'Pruebe2CNF -- help' para más información" << std::endl;
    return 1;
  }

  try {
    std::ifstream archivo_entrada(argv[1]);

    if (!archivo_entrada.is_open()) {
      throw std::runtime_error("Error al abrir el archivo de entrada");
    }

    std::ofstream archivo_salida(argv[2]);

    if (!archivo_salida.is_open()) {
      throw std::runtime_error("Error al abrir el archivo de salida");
    }

    std::ofstream archivo_gramatica("gramatica.gra");
    if (!archivo_gramatica.is_open()) {
      throw std::runtime_error("No se pudo abrir el archivo");
    }
    // End of Argument Handling





  } catch (std::runtime_error &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
