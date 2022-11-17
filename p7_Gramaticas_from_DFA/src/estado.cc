//
// Created by grass on 16/11/2022.
//

#include "../include/estado.h"
std::ostream &operator<<(std::ostream &os, const Estado &estado) {

  os << estado.estado_ << ": ";
  for (auto &i : estado.transiciones_) {
    os << "(" << i.first << ":" << i.second->estado_ << ") ";
  }

  return os;
}

/**
 * Constructor de la clase Estado
 *
 * @param estado
 * @param vector_estados
 * @param alfabeto
 * @throws std::runtime_error si el estado no es valido
 *
 */
Estado::Estado(const std::string &estado, std::vector<Estado> &vector_estados, Alfabeto &alfabeto) {
  // separamos la cadena en tokens
  std::stringstream ss(estado);
  std::string token;
  std::vector<std::string> tokens;
  while (std::getline(ss, token, ' ')) {
    tokens.push_back(token);
  }

  // la primera posicion es el estado
  estado_ = std::stoi(tokens[0]);

  // la segunda posicion indica si es de aceptacion o no
  aceptacion_ = std::stoi(tokens[1]);

  // a partir de la cuarta posicion, se indica la transicion primero el simbolo y luego el estado
  // recorremos los tokens de 2 en 2
  for (int i = 3; i < tokens.size(); i += 2) {

    // el primer token es el simbolo
    Simbolo simbolo(tokens[i]);
    if (!alfabeto.Pertenece(simbolo)) {
      throw std::runtime_error("El simbolo " + simbolo.ToString() + " no Pertenece al alfabeto");
    }

    // el segundo token es el estado
    Estado *estado_a_transitar = &vector_estados[std::stoi(tokens[i + 1])];
    // se crea la transicion
    transiciones_.emplace_back(std::make_pair(simbolo, estado_a_transitar));
  }
}

/**
 * Comprueba si el estado es de aceptacion
 * @return true si es de aceptacion, false en caso contrario
 */
bool Estado::es_aceptacion() const {
  return aceptacion_;
}

/**
 * Comprueba si el estado al que transita existe
 * @param simbolo
 * @returns el puntero al estado que se va a transitar si existe, nullptr en caso contrario
 */
Estado *Estado::transicion(const Simbolo &simbolo) {
  for (auto &i : transiciones_) {
    if (i.first == simbolo) {
      return i.second;
    }
  }
  return nullptr;
}

/**
 * Convierte el estado a string
 * @return string con el estado
 */
std::string Estado::to_string() const {
  return std::to_string(estado_);
}

/**
 * Devuelve el vector de Transiciones
 * @return
 */
std::vector<std::pair<Simbolo, Estado *>> Estado::get_transiciones() const {
  return transiciones_;
}

/**
 * Devuelve el estado
 * @return
 */
int Estado::get_id() const {
  return estado_;
}
