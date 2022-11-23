//
// Created by grass on 21/11/2022.
//

#include "../include/gramatica.h"

/**
 * @brief Constructor de la clase Gramatica
 * @param archivo archivo de texto que contiene la gramatica (extensión ".gra")
 *
 */

Gramatica::Gramatica(std::ifstream &archivo) {

  std::string linea;
  std::getline(archivo, linea);

  int n_terminal = std::stoi(linea);
  for (int i = 0; i < n_terminal; i++) {
    std::getline(archivo, linea);
    simbolos_terminales_.insert(Simbolo(linea));
  }

  std::getline(archivo, linea);
  int n_nterminales = std::stoi(linea);
  for (int i = 0; i < n_nterminales; i++) {
    std::getline(archivo, linea);
    simbolos_no_terminales_.insert(Simbolo(linea));
  }

  std::getline(archivo, linea);
  simbolo_inicial_ = Simbolo(linea);

  std::getline(archivo, linea);
  int n_producciones = std::stoi(linea);

  for (int i = 0; i < n_producciones; i++) {
    std::getline(archivo, linea);
    std::stringstream ss(linea);

    Simbolo arrow;
    Simbolo no_terminal;
    Simbolo produccion;

    ss >> no_terminal;
    ss >> arrow;
    ss >> produccion;

    // crea una producción nueva en caso de que no exista
    if (producciones_.find(no_terminal) == producciones_.end()) {
      producciones_[no_terminal] = producciones_.insert({no_terminal, {}}).first->second;
    }
    producciones_[no_terminal].push_back(produccion);
  }
}

/**
 * @brief Metodo que escribe la gramatica en un archivo de texto
 * @param archivo archivo de textoal que se va a escribir (extensión ".gra")
 */
void Gramatica::EscribirGramatica(std::basic_ostream<char> &archivo) const {
  archivo << simbolos_no_terminales_.size() << std::endl;
  for (const auto &simbolo : simbolos_no_terminales_) {
    archivo << simbolo.ToString() << std::endl;
  }
  archivo << simbolos_terminales_.size() << std::endl;
  for (const auto &simbolo : simbolos_terminales_) {
    archivo << simbolo.ToString() << std::endl;
  }
  archivo << simbolo_inicial_.ToString() << std::endl;

  int n_producciones = 0;
  for (const auto &produccion : producciones_) {
    n_producciones += produccion.second.size();
  }
  archivo << n_producciones << std::endl;
  for (const auto &produccion : producciones_) {
    for (const auto &simbolo : produccion.second) {
      archivo << produccion.first.ToString() << " -> " << simbolo.ToString() << std::endl;
    }
  }
}


/**
 * @brief Metodo que pasa la gramatica a forma normal de chomsky
 * @return Gramatica en forma normal de chomsky
 *
 */
Gramatica Gramatica::ToChomsky() const {
  Gramatica gramatica_chomsky = Gramatica(*this);
  std::set<Simbolo> simbolos_usados;
  // primera pasada: sustituir las producciones de la forma A -> aB por A -> XB y X -> a
  for (const auto &produccion : gramatica_chomsky.producciones_) {
    for (const auto &simbolo : produccion.second) {
      // comprobamos que la producción es de la forma A -> a
      if (simbolo.EsTerminalUnitario()) {
        continue;
      }

      // comprobamos que la producción es de la forma A -> BC
      if (simbolo.EsNoTerminalFNC()) {
        continue;
      }

      for (const auto &c : simbolo.ToString()) {
        if (islower(c) && simbolos_usados.find(Simbolo(std::string(1, c))) == simbolos_usados.end()) {
          Simbolo new_non_terminal = Simbolo::GetNewNonTerminal();
          simbolos_usados.insert(Simbolo(std::string(1, c)));
          gramatica_chomsky.simbolos_no_terminales_.insert(new_non_terminal);
          gramatica_chomsky.producciones_[new_non_terminal] = {Simbolo(std::string(1, c))};

          for (auto &v_produccion : gramatica_chomsky.producciones_) {
            if (v_produccion.second.size() == 1 && v_produccion.second[0].EsTerminalUnitario()) {
              continue;
            }
            for (auto &prod : v_produccion.second) {
              for (auto &letra : prod) {
                if (letra == c) {
                  letra = new_non_terminal.ToString()[0];
                }
              }
            }
          }
        }
      }
    }
  }
  std::cout << "primera pasada:\n" << gramatica_chomsky << std::endl;

  // segunda pasada: sustituir las producciones de la forma A -> ABC por A -> AD y D -> BC
  // otro ejemplo A -> BCDE por A -> BCG y G -> DE y luego A -> BH y H -> CG
  for (const auto &produccion : gramatica_chomsky.producciones_) {
    for (const auto &simbolo : produccion.second) {
      if (simbolo.EsTerminalUnitario()) {
        continue;
      }
      if (simbolo.EsNoTerminalFNC()) {
        continue;
      }

      while (simbolo.ToString().size() >= 3) {
        Simbolo left_part(simbolo.ToString().substr(0, simbolo.ToString().size() - 2));
        Simbolo right_part(simbolo.ToString().substr(simbolo.ToString().size() - 2, 2));

        // creamos un nuevo no terminal para la parte derecha
        Simbolo new_non_terminal = Simbolo::GetNewNonTerminal();
        gramatica_chomsky.simbolos_no_terminales_.insert(new_non_terminal);

        // asignamos la producción del nuevo no terminal
        gramatica_chomsky.producciones_[new_non_terminal] = {Simbolo(right_part)};

        // sustituimos la producción en el resto de producciones
        for (auto &v_produccion : gramatica_chomsky.producciones_) {
          if (v_produccion.second.size() == 1 && v_produccion.second[0].EsTerminalUnitario()) {
            continue;
          }
          for (auto &prod : v_produccion.second) {
            // ir comprobando de dos en dos
            for (int i = 0; i < prod.ToString().size() - 1; i++) {
              if (Simbolo(prod.ToString().substr(i, 2)) == right_part && v_produccion.first != new_non_terminal) {
                prod = left_part + new_non_terminal;
              }
            }
          }
        }
      }
    }
  }

  std::cout << "Segunda pasada:\n" << gramatica_chomsky << std::endl;

  return gramatica_chomsky;
}

std::ostream &operator<<(std::ostream &os, const Gramatica &gramatica) {
  os << "Simbolos no terminales: " << std::endl;
  for (const auto &simbolo : gramatica.simbolos_no_terminales_) {
    os << simbolo.ToString() << std::endl;
  }
  os << "Simbolos terminales: " << std::endl;
  for (const auto &simbolo : gramatica.simbolos_terminales_) {
    os << simbolo.ToString() << std::endl;
  }
  os << "Simbolo inicial: " << std::endl;
  os << gramatica.simbolo_inicial_.ToString() << std::endl;
  os << "Producciones: " << std::endl;
  for (const auto &produccion : gramatica.producciones_) {
    for (const auto &simbolo : produccion.second) {
      os << produccion.first.ToString() << " -> " << simbolo.ToString() << std::endl;
    }
  }
  return os;
}



