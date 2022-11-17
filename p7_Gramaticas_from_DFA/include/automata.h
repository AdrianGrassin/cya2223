#ifndef P7_GRAMATICAS_FROM_DFA_SRC_AUTOMATA_H_
#define P7_GRAMATICAS_FROM_DFA_SRC_AUTOMATA_H_

class Gramatica;

#include "estado.h"
#include "cadena.h"
#include "alfabeto.h"
#include "estado.h"
#include "fstream"
#include "gramatica.h"

/**
 * @class Automata
 * @brief Clase que representa un automata finito determinista
 * @details Esta clase representa un automata finito determinista, el cual se puede construir a partir de un archivo de texto
 * que contenga la informacion necesaria para construirlo.
 *
 *
 */
class Automata {
 public:
  Automata() = default;
  explicit Automata(std::ifstream &archivo);

  [[nodiscard]] Alfabeto GetAlfabeto() const;
  [[nodiscard]] std::vector<Estado> GetEstados() const;

  Gramatica ConverToGrammar() const;

  [[nodiscard]] bool EvaluaLaCadena(const Cadena &cadena) const;
  friend std::ostream &operator<<(std::ostream &os, const Automata &automata);

 private:
  int estado_inicial_{};
  std::vector<Estado> estados_;
  Alfabeto alfabeto_;

};

#endif //P7_GRAMATICAS_FROM_DFA_SRC_AUTOMATA_H_
