//
// Created by Adri on 13/10/2022.
//

#include <stack>
#include "Calc.h"

void Calc::readfile(std::ifstream &file,
                    std::vector<std::pair<Alfabeto *, Lenguaje *>> &lista,
                    std::vector<std::string> &operaciones) {

  std::string line;
  if (file.is_open()) {
    while (getline(file, line)) {
      if (line[3] == '=') {
        auto *dummy_alf = new Alfabeto(reformatinput(line));
        auto *dummy_cad = new Lenguaje(reformatinput(line), dummy_alf);
        lista.emplace_back(dummy_alf, dummy_cad);
      } else {
        line += ' ';
        std::string word_buffer;
        for (auto &charac : line) {
          if (charac == ' ') {
            operaciones.emplace_back(word_buffer);
            word_buffer.clear();
          }
          word_buffer += charac;
        }
      }
    }

  } else {
    throw std::runtime_error("El primer archivo no se encontró o no se pudo abrir");
  }
}

std::string Calc::reformatinput(std::string &line) {
  std::string linetomodify = line.substr(line.find_first_of('{'), line.find_first_of('}'));
  for (auto &i : linetomodify) {
    if (i == ',') {
      linetomodify.erase(linetomodify.find_first_of(','), 1);
    }
  }
  linetomodify = linetomodify.substr(1, linetomodify.size() - 2) + " ";
  return linetomodify;
}

Calc::Calc(std::ifstream &file) {
  readfile(file, definiciones_, operaciones_);  // lee el fichero y va guardando las definiciones y operaciones

}

void Calc::operate() {
  // rpn algorithm to evaluate the operations
  // Languajes will be in the form of L1, L2, L3, etc.
  // Operations will be in the form of +, -, *, |, ∧ and !
  // + represents concatenation, it's done by the function concatenar
  // - represents difference, it's done by the function diferencia
  // * represents star, it's done by the function potencia
  // | represents union
  // ∧ represents intersection
  // ! represents complement
  // the result will be stored as a string in the vector resultados_
  std::stack<std::string> pila;
  Lenguaje* resultado;
  for (auto &i : operaciones_) {
    if(i[0] == 'L') {
      pila.push(i);
    }
    else if(i[0] == '+' || i[0] == '-' || i[0] == '|' || i[0] == '!' || i[0] == '^' || i[0] == '*'){
      perform_operation(i[0], pila);
    }
  }
}

Lenguaje Calc::concatenar(Lenguaje &l1, Lenguaje &l2) {
  Lenguaje result;
  result = l1 + l2;
  return result;
}

Lenguaje Calc::diferencia(Lenguaje &l1, Lenguaje &l2) {
  Lenguaje result;
  result = l1 - l2;
  return result;
}

Lenguaje Calc::potencia(Lenguaje &l1, int &n) {
  Lenguaje result;
  result = l1 * n;
  return result;
}

Lenguaje Calc::union_len(Lenguaje &l1, Lenguaje &l2) {
  Lenguaje result;
  result = l1 | l2;
  return result;
}

Lenguaje Calc::interseccion(Lenguaje &l1, Lenguaje &l2) {
  Lenguaje result;
  result = l1 ^ l2;
  return result;
}
Lenguaje Calc::inversa(Lenguaje &l1) {
  Lenguaje result;
  result = !l1;
  return result;
}
void Calc::perform_operation(char op, std::stack<std::string> &pila) {

}

