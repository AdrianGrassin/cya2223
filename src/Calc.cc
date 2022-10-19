//
// Created by Adri on 13/10/2022.
//

#include <stack>
#include "../include/Calc.h"

void Calc::readfile(std::ifstream &file,
                    std::vector<std::pair<Alfabeto *, Lenguaje *>> &lista,
                    std::vector<std::vector<std::string>> &operaciones) {

  std::string line;
  if (file.is_open()) {
    while (getline(file, line)) {
      if (line.find('=') != std::string::npos) {
        auto *dummy_alf = new Alfabeto(reformatinput(line));
        auto *dummy_len = new Lenguaje(reformatinput(line), dummy_alf);
        dummy_len->set_tag(line.substr(0, line.find(' ')));
        lista.emplace_back(dummy_alf, dummy_len);
      } else { // operaciones
        line += ' ';
        std::string word_buffer;
        std::vector<std::string> operacion;
        for (auto &charac : line) {
          if (charac == ' ') {
            operacion.emplace_back(word_buffer);
            word_buffer.clear();
          } else {
            word_buffer += charac;
          }
        }
        operaciones.emplace_back(operacion);
      }
    }

  } else {
    throw std::runtime_error("El primer archivo no se encontró o no se pudo abrir");
  }
}

std::string Calc::reformatinput(std::string &line) {
  if (line.find('{') == std::string::npos || line.find('}') == std::string::npos) {
    throw std::runtime_error(
        "El formato de linea " + line + " no es correcto.\nSe esperaba un \"{\" y un \"}\" para definir el lenguaje");
  }

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
  std::stack<elemento_pila> pila;
  Lenguaje *resultado;
  for (auto &i : operaciones_) {
     for (auto &j : i) {
      if (is_str_a_lng(j)) {
        pila.push({Lenguaje_en_pila, definiciones_[findbytag(j)].second});
      } else if (isdigit(j[0])) {
        pila.push({Numero, definiciones_[j[0] - '0'].second});
      } else {
        perform_operation(j[0], pila);
      }
    }
    resultados_.emplace_back(pila.top().datos.lenguaje);
    pila.pop();
  }
  refine_result();
}

void Calc::perform_operation(char op, std::stack<elemento_pila> &pila) {
  Lenguaje *l1, *l2;
  int n;
  switch (op) {
    case '+':l1 = pila.top().datos.lenguaje;
      pila.pop();
      l2 = pila.top().datos.lenguaje;
      pila.pop();
      pila.push({Lenguaje_en_pila, new Lenguaje(concatenar(*l1, *l2))});
      break;
    case '-':l1 = pila.top().datos.lenguaje;
      pila.pop();
      l2 = pila.top().datos.lenguaje;
      pila.pop();
      pila.push({Lenguaje_en_pila, new Lenguaje(diferencia(*l1, *l2))});
      break;
    case '|':l1 = pila.top().datos.lenguaje;
      pila.pop();
      l2 = pila.top().datos.lenguaje;
      pila.pop();
      pila.push({Lenguaje_en_pila, new Lenguaje(union_len(*l1, *l2))});
      break;
    case '!':l1 = pila.top().datos.lenguaje;
      pila.pop();
      pila.push({Lenguaje_en_pila, new Lenguaje(inversa(*l1))});
      break;
    case '^':l1 = pila.top().datos.lenguaje;
      pila.pop();
      l2 = pila.top().datos.lenguaje;
      pila.pop();
      pila.push({Lenguaje_en_pila, new Lenguaje(interseccion(*l1, *l2))});
      break;
    case '*':l1 = pila.top().datos.lenguaje;
      pila.pop();
      n = pila.top().datos.numero;
      pila.pop();
      pila.push({Lenguaje_en_pila, new Lenguaje(potencia(*l1, n))});
      break;
    default: throw std::runtime_error("Unknown operation");
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
  Lenguaje result(l1.interseccion(l2), l1.getalfabeto());
  return result;
}
Lenguaje Calc::inversa(Lenguaje &l1) {
  Lenguaje result;
  result = !l1;
  return result;
}

void Calc::get_resultado() {
  std::string resultado;
  for (auto &i : resultados_) {
    for (auto &j : i->get_cadenas_del_lenguaje()) {
      std::cout << *j << " ";
    }
    std::cout << std::endl;
  }
}

void Calc::refine_result() {
  for (auto &i : resultados_) {
    for (auto &j : i->get_cadenas_del_lenguaje()) {
      if (j->get_real_lenght() == 0 && j->get_chain_as_string().size() > 1) {
        i->get_cadenas_del_lenguaje().erase(j);         // borra && &&& &&&& etc
        continue;
      }
      if (j->get_real_lenght() >= 1) {
        j->erase_cadenavacia();         // borra cadenas vacias
      }
    }
  }
}

bool Calc::is_str_a_lng(std::string &str) {
  for (auto &i : definiciones_) {
    if (i.second->get_tag() == str) {
      return true;
    }
  }
  return false;
}

int Calc::findbytag(std::string &str) {
  for (int i = 0; i < definiciones_.size(); i++) {
    if (definiciones_[i].second->get_tag() == str) {
      return i;
    }
  }
  return -1;
}
