#include "../include/gramatica.h"
/**
 * Constructor de la clase Gramatica
 *
 * @param dfa Se le pasa un automata finito determinista para poder generar la gramatica
 *
 */

Gramatica::Gramatica(const Automata &dfa) {
  // Se obtienen los simbolos terminales y no terminales
  alfabeto_ = dfa.GetAlfabeto();

  // Se obtiene el estado inicial
  simbolo_inicial_ = Simbolo("S");

  // Se obtienen los estados del autómata
  std::vector<Estado> estados = dfa.GetEstados();

  // se generan las producciones
  for (const auto &estado : estados) {
    producciones_.emplace_back(estado, alfabeto_);
  }
}

std::ostream &operator<<(std::ostream &os, const Gramatica &gramatica) {
  os << "--- Gramatica ---" << std::endl;
  for (const auto &produccion : gramatica.producciones_) {
    os << produccion << std::endl;
  }
  return os;
}

void Gramatica::write(std::ofstream &os) const {
    for (const auto &produccion : producciones_) {
        os << produccion << std::endl;
    }
}

