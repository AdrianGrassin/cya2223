#include <random>
#include "include/utilities.h"
#include "include/BigInt.h"





/***
 * Argumentos esperados:
 *  -> cat <fichero> ./main <opcion>(opcional) <numero>(opcional si se usa alguna opcion)
 *
 *  <opciones>:
 *  -h: Muestra esta ayuda
 *  -n <cota>: <cota> es el valor de cota de cambio entre el operador '*' de la clase BigInt y
 *         el algoritmo de Karatsuba, que corresponderia a la implementacion hibrida de ambos algoritmos.
 *  -r (random) <digitos>: es el numero de digitos que tiene que tener cada numero aleatorio.
 *  -k: Utiliza el algoritmo de Karatsuba para multiplicar.
 *  -m: Utiliza el operador '*' de la clase BigInt para multiplicar.
 *
 *
 *  <ejemplo basico>:
 *  -> cat <fichero_a> <fichero_b> | ./main | diff - <fichero_resultado>
 *
 *
 *  <estructura del fichero de entrada> :
 *  1| <numero de cualquier longitud>
 *  2|
 *
 * */


int main(int argc, char *argv[]) {

  try {

    std::vector<std::string> args;
    for (int i = 0; i < argc; i++) {
      args.emplace_back(argv[i]);
    }

    /***
     * @if comprueba que al menos un argumento es de tipo -h y en ese caso muestra la ayuda y termina el programa.
     * */
    if (std::any_of(args.begin(), args.end(), [](const std::string &arg) { return arg == "-h"; })) {
      help();
      return 0;
    }

    int arg_option = 0;

    if (argc >= 2) {
      arg_option = case_from_arg(args[1]);
    }

    std::string line;
    std::vector<std::string> numbers;

    /***
     * Comprobamos los argumentos y en funcion de ellos, realizamos las operaciones correspondientes.
     */

    if (argc == 1) {
      while (std::getline(std::cin, line)) {
        numbers.emplace_back(line);
      }
    } else if (std::string(argv[1]) == "-r") {
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dis(1, 9);

      for (int i = 0; i < 2; i++) {
        std::string number;
        for (int j = 0; j < std::stoi(args[2]); j++) {
          number += std::to_string(dis(gen));
        }
        numbers.emplace_back(number);
      }
    } else {
      while (std::getline(std::cin, line)) {
        numbers.emplace_back(line);
      }
    }

    /***
     * Ahora comprobaremos que se ha introducido por entrada estandar dos números separados por un salto de línea.
     * */

    if (numbers.size() != 2) {
      std::cout << "Error: Se esperaban dos numeros separados por un salto de linea." << std::endl;
      return 1;
    }


    BigInt a(numbers[0]);
    BigInt b(numbers[1]);


    BigInt one(86);
    std::cout << Length(one) << std::endl;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds{};

    /***
     * @switch
     *  case 0: Karatsuba
     *  case 1: Multiplicacion normal
     *  case 2: Multiplicacion dependiente de una cota
     *  case 3: Multiplicación de números aleatorios de un tamaño dado
     *  default: Error
     */

    switch (arg_option) {
      case 0 :std::cout << "- Multiplicacion con el algoritmo de Karatsuba -" << std::endl;

        std::cout << "a: " << a << std::endl;
        std::cout << "b: " << b << std::endl;

        start = std::chrono::high_resolution_clock::now();
        Karatsuba(a, b);
        end = std::chrono::high_resolution_clock::now();

        elapsed_seconds = end - start;
        std::cout << Karatsuba(a, b) << std::endl;
        std::cout << "Tiempo: " << elapsed_seconds.count() * 1000 << "ms" << std::endl;

        break;
      case 1 : std::cout << "- Multiplicacion con el algoritmo de hibrido: ";
        if (argc < 3) { throw std::invalid_argument("No se especifico la cota"); }
        std::cout << "Cota dada:" << argv[2] << std::endl;

        if (std::stoi(argv[2]) < 0) {
          throw std::invalid_argument("La cota debe ser un numero positivo");
        }

        if (Length(a) < std::stoi(argv[2]) && Length(b) < std::stoi(argv[2])) {
          std::cout << "Multiplicacion con el operador * de la clase BigInt" << std::endl;

          start = std::chrono::system_clock::now();
          a * b;
          end = std::chrono::system_clock::now();

          elapsed_seconds = end - start;
          std::cout << a * b << std::endl;
          std::cout << "Tiempo: " << elapsed_seconds.count() * 1000 << "ms" << std::endl;

        } else {
          std::cout << "Multiplicacion con el algortimo de Karatsuba" << std::endl;
          std::cout << "Resultado:" << std::endl;
          start = std::chrono::high_resolution_clock::now();
          Karatsuba(a, b);
          end = std::chrono::high_resolution_clock::now();

          elapsed_seconds = end - start;
          std::cout << a * b << std::endl;
          std::cout << "Tiempo: " << elapsed_seconds.count() * 1000 << "ms" << std::endl;
        }
        break;
      case 2 : std::cout << "- Multiplicacion con el algoritmo de Karatsuba -" << std::endl;
        std::cout << "Random :" << argv[2] << std::endl;

        std::cout << "Numero 1: " << a << std::endl << std::endl;
        std::cout << "Numero 2: " << b << std::endl << std::endl;

        start = std::chrono::system_clock::now();
        std::cout << Karatsuba(a, b) << std::endl;
        end = std::chrono::system_clock::now();

        elapsed_seconds = end - start;
        std::cout << "Tiempo: " << elapsed_seconds.count() * 1000 << "ms" << std::endl;
        break;
      case 3 : std::cout << "- Multiplicacion con el operador * de la clase BigInt -" << std::endl;
        start = std::chrono::high_resolution_clock::now();
        a * b;
        end = std::chrono::high_resolution_clock::now();
        std::cout << "Resultado:\n" << a * b << std::endl;
        elapsed_seconds = end - start;
        std::cout << "Tiempo de ejecucion: " << elapsed_seconds.count() * 1000 << "ms" << std::endl;

        break;

      default: throw std::invalid_argument(argv[1] + std::string(" no es un argumento valido."));
    }

  } catch (std::invalid_argument &e) {
    std::cout << "Argumentos invalidos: " << e.what() << std::endl;
    return 1;

  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
    return 1;

  }

  return 0;
}
