#include "../include/produccion.h"

/**
 * Constructor de la clase Produccion que recibe un estado con sus transiciones y genera la produccion correspondiente
 * @param estado
 */
Produccion::Produccion(const Estado &estado, const Alfabeto &alfabeto) {
  if (estado.es_aceptacion()) {
    produccion_.emplace_back("&");
  }

  alfabeto_ = alfabeto;
  // letra para el no terminal
  no_terminal_ = Simbolo(EstadoToString(estado));

  // recorrer las transiciones para crear las producciones
  for (auto &transicion : estado.get_transiciones()) {
    std::string produccion = transicion.first.ToString();
    produccion += EstadoToString(*transicion.second);

    produccion_.emplace_back(produccion);
  }
}

/**
 * Convierte el estado a un identificador de no terminal
 * @param estado
 * @return string con el identificador del no terminal
 *
 */
std::string Produccion::EstadoToString(const Estado &estado) {
  if (estado.get_id() == 0) {
    return "S";
  } else {
    char no_terminal = (estado.get_id() - 1 + 'A');
    return &no_terminal;
  }
}

/**
 * Impresion de la produccion
 * De la forma: A -> aB | bC | &
 *
 */
std::ostream &operator<<(std::ostream &os, const Produccion &produccion) {
  os << produccion.no_terminal_ << " -> ";
  for (int i = 0; i < produccion.produccion_.size(); ++i) {
    os << produccion.produccion_[i];
    if (i != produccion.produccion_.size() - 1) {
      os << " | ";
    }
  }
  return os;
}



