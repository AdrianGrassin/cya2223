/**
 * @mainpage [Universidad de La Laguna]
 * Escuela Superior de Ingeniería y Tecnología
 * -------------------------------------------
 * Computabilidad y Algoritmia
 * -----------------------------------------
 * Correo: alu0101349480@ull.edu.es
 *
 *  Práctica #04: Símbolos, alfabetos y cadenas
 *  --------------------------------------------
 *  En esta práctica 1 se usan las clases de bucles, comentarios, declaraciones y analizer para poder leer un fichero y
 *  analizar el contenido del mismo. Se usan expresiones regulares para poder identificar los diferentes tipos de datos
 *  que se encuentran en el fichero.
 *
 * GitHub - not posted
 * ------
 * @version 1.0
 * @date 27/10/2022
 * @author Adrian Grassin Luis
 *
 * @file main.cc
 * @brief Main bastante sencillo.
 */


#include <iostream>
#include <fstream>
#include <string>
#include "../include/analizer.h"

int hola;
int hi = 10;
double yup;
double yu = 10;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "Usage: ./analize_code_p4 <filename> <fileout>" << std::endl;
    return 1;
  }

  std::ifstream file(argv[1]);
  std::string line;

  std::ofstream fileout(argv[2]);

  try {
    analizer text_search(file);
    fileout << "PROGRAMA: " << argv[1] << std::endl;
    fileout << text_search;

  } catch (std::exception &error) {
    std::cout << error.what() << std::endl;
  }

  return 0;
}

