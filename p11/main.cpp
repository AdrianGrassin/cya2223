#include <iostream>
#include "include/Algoritmos.h"

#define MONEDAS {1, 2, 5, 10, 20, 50, 100, 200}
#define MONEDASYBILLETES {1, 2, 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help") {
      std::cout << "Uso: " << "./cambio" << " <total> <opcion>" << std::endl << std::endl;
      std::cout << "Este programa calcula el cambio de una cantidad de dinero dada en monedas." << std::endl;
      std::cout << "El primer argumento es el total a cambiar." << std::endl;
      std::cout << "El segundo argumento es opcional y determina el modo de funcionamiento del programa:" << std::endl;
      std::cout << "\t-b : Cambio con billetes y monedas." << std::endl;
      std::cout << "\t-o : Cambio realizado con un algoritmo de complejidad O(m)." << std::endl;
      std::cout << "\t - : El programa se ejecuta en modo monedas de hasta 2 euros" << std::endl;

      return 0;
    }

    double total = std::stod(argv[1], nullptr);
    std::vector<int> valores_cambio = MONEDAS;
    std::vector<int> resultado = calcular_monedas(total, valores_cambio);

    std::cout << "monedas: " << total << std::endl;
    std::cout << sol_str_tipo(resultado) << std::endl;
    std::cout << "Numero de monedas: " << resultado.size() << std::endl;

    return 0;
  }

  if (argc == 3) {
    std::vector<int> resultado;

    if (std::string(argv[1]) == "-b") {
      std::vector<int> valores_cambio = MONEDASYBILLETES;
      resultado = calcular_monedas(std::stod(argv[2]), valores_cambio);
    }

    if (std::string(argv[1]) == "-o") {
      std::vector<int> valores_cambio = MONEDAS;
      resultado = calcular_monedas_eficiente(std::stod(argv[2]), valores_cambio);
    }

    std::cout << "monedas: " << argv[2] << std::endl;
    std::cout << sol_str_tipo(resultado) << std::endl;
    std::cout << "Numero de monedas y billetes: " << resultado.size() << std::endl;

    return 0; // Salida normal
  }


}
