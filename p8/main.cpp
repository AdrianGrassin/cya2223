#include <iostream>
#include "include/gramatica.h"

int main(int argc, char** argv) {
  if (argc >= 1 && std::string(argv[1]) == "--help" ) {
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

    Gramatica gramatica(archivo_entrada);
    gramatica.EscribirGramatica(archivo_gramatica);

    Gramatica gramatica_chomsky = gramatica.ToChomsky();
    gramatica_chomsky.EscribirGramatica(archivo_salida);

    archivo_entrada.close();
    archivo_salida.close();

  } catch (std::runtime_error &e) {
    std::cout << e.what() << std::endl;
  }

}
