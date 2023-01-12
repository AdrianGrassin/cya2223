#include "../include/utilities.h"

void help() {
  std::cout << "Argumentos esperados: " << std::endl;
  std::cout << "  -> ./main <opcion>(opcional) <numero>(dependiente del argumento)" << std::endl << std::endl;
  std::cout << " <opciones>: " << std::endl;
  std::cout << "\t-h: Muestra esta ayuda" << std::endl;
  std::cout << "\t-n <cota> : <cota> es el valor de cota de cambio entre el operador '*' de la clase BigInt y\n\t"
               " el algoritmo de Karatsuba, que corresponderia a la implementacion hibrida de ambos algoritmos."
            << std::endl;
  std::cout << "\t-r (random) <digitos> : es el numero de digitos que tiene que tener cada numero aleatorio."
            << std::endl;
  std::cout << "\t-k : Utiliza el algoritmo de Karatsuba para multiplicar." << std::endl;
  std::cout << "\t-m : Utiliza el operador '*' de la clase BigInt para multiplicar." << std::endl << std::endl;
  std::cout << "Por defecto el programa utiliza el algortimo de Karatsuba para multiplicar." << std::endl;
}

int case_from_arg(std::string& argument) {
    if (argument == "-k") {
        return 0;
    } else if (argument == "-n") {
        return 1;
    } else if (argument == "-r") {
        return 2;
    } else if (argument == "-m") {
        return 3;
    } else {
        return -1;
    }
}


