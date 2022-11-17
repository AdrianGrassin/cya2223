//
// Created by grass on 16/11/2022.
//

#include "../include/automata.h"

/**
 * Constructor de la clase Automata
 * @param archivo Ha de tener el formato de un automata y tener una extension ".fa"
 * @throws std::runtime_error Si el numero de estados no coincide con el numero de lineas del fichero sin contar las
 * tres iniciales
 * @throws std::runtime_error Si se definió más de un estado inicial o ninguno
 *
 */

Automata::Automata(std::ifstream &archivo) {

  std::string linea;
  std::vector<std::string> lineas;
  while (getline(archivo, linea)) {
    lineas.push_back(linea);
  }

  std::string alfabeto = lineas[0];
  alfabeto_ = Alfabeto(lineas[0]);

  if (std::stoi(lineas[1]) != lineas.size() - 3) {
    throw std::runtime_error("El numero de estados no coincide con el numero de estados indicado");
  }
  estados_.resize(std::stoi(lineas[1]));

  if (lineas[2].size() > 1) {
    throw std::runtime_error("Solo puede haber un estado inicial");
  } else if (lineas[2].size() == 0) {
    throw std::runtime_error("Debe haber un estado inicial");
  } else if (std::stoi(lineas[2]) >= estados_.size() || std::stoi(lineas[2]) < 0) {
    throw std::runtime_error("El estado inicial no existe");
  }
  estado_inicial_ = std::stoi(lineas[2]);

  for (int i = 3; i < lineas.size(); ++i) {
    estados_[i - 3] = Estado(lineas[i], estados_, alfabeto_);
  }
}

std::ostream &operator<<(std::ostream &os, const Automata &automata) {
  os << "--- Automata ---" << std::endl;
  os << "Alfabeto: " << automata.alfabeto_ << std::endl;
  os << "Estados: " << std::endl;
  for (auto &i : automata.estados_) {
    os << i << std::endl;
  }

  return os;
}

/**
 * Evalua una cadena en el automata
 * @param cadena
 * @return true si la cadena es aceptada por el automata, false en caso contrario
 */
bool Automata::EvaluaLaCadena(const Cadena &cadena) const {
  Estado estado_actual = estados_[estado_inicial_];
  for (auto &i : cadena) {
    if (!alfabeto_.Pertenece(i)) {
      std::cout << "El simbolo " << i.ToString() << " no Pertenece al alfabeto, la cadena no es valida" << std::endl;
      return false;
    }

    Estado *estado_siguiente = estado_actual.transicion(i);

    if (estado_siguiente == nullptr) {
      std::cout << "No existe transicion para el simbolo " << i.ToString() << " en el estado "
                << estado_actual.to_string() << std::endl;
      return false;
    }

    estado_actual = *estado_siguiente;
  }

  if (estado_actual.es_aceptacion()) {
    std::cout << "La cadena \"" + cadena.to_string() + "\" es valida" << std::endl;
    return true;
  } else {
    std::cout << "La cadena \"" + cadena.to_string() + "\" no es valida" << std::endl;
    return false;
  }
}

Alfabeto Automata::GetAlfabeto() const {
  return alfabeto_;
}

std::vector<Estado> Automata::GetEstados() const {
  return estados_;
}
Gramatica Automata::ConverToGrammar() const {
  return Gramatica(*this);
}



