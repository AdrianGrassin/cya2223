//
// Created by grass on 06/10/2022.
//

#include "../include/Lenguaje.h"

Lenguaje::Lenguaje(const std::string &line, Alfabeto *alfabeto) {
  alfabeto_ = alfabeto;
  std::string string_buffer;
  for (const auto &caracter : line) {
    if (caracter == ' ' && line != "Lenguaje Vacío") {
      cadenas_del_lenguaje.insert(new Cadena(string_buffer, alfabeto));
      string_buffer.clear();
    }
    string_buffer += caracter;
  }
}

std::ostream &operator<<(std::ostream &out, Lenguaje &len) {
  out << "L = { ";
  for (auto cadena : len.cadenas_del_lenguaje) {
    out << *cadena << " ";
  }
  out << "} ";
  if (len.cadenas_del_lenguaje.empty())
    out << "- Lenguaje Vacío ";

  return out;
}

void Lenguaje::print_size_of_chains() {
  for (auto &a : cadenas_del_lenguaje) {
    std::cout << a->get_real_lenght() << " ";
  }
  std::cout << std::endl;
}
std::string Lenguaje::inversa() {
  std::string lenguaje_inv;
  for (auto &a : cadenas_del_lenguaje) {
    lenguaje_inv += a->inversa();
    lenguaje_inv += ' ';
  }
  return lenguaje_inv;
}

std::string Lenguaje::concatenacion(Lenguaje &len) {
  std::string lenguajes_L1L2_concat;
  for (const auto &cad_L1 : cadenas_del_lenguaje) {
    if (cad_L1->get_real_lenght() == 0) { continue; } // caso  L1 = { & }
    for (const auto &cad_L2 : len.cadenas_del_lenguaje) {
      if (cad_L2->get_real_lenght() == 0) {  // caso L2 = { & }
        lenguajes_L1L2_concat += cad_L1->get_chain_as_string();
        lenguajes_L1L2_concat += ' ';
        continue;
      }
      lenguajes_L1L2_concat += cad_L1->get_chain_as_string() + cad_L2->get_chain_as_string();
      lenguajes_L1L2_concat += ' ';
    }
  }
  return lenguajes_L1L2_concat;
}

std::string Lenguaje::op_union(Lenguaje &len) {
  std::string lenguajeL1L2;
  std::set<std::string> lenguajeunion;
  for (const auto &value_L1 : cadenas_del_lenguaje) {
    if (value_L1->get_real_lenght() != 0)
      lenguajeunion.insert(value_L1->get_chain_as_string());
  }
  for (const auto &value_L2 : len.cadenas_del_lenguaje) {
    if (value_L2->get_real_lenght() != 0)
      lenguajeunion.insert(value_L2->get_chain_as_string());
  }

  for (const auto &a : lenguajeunion) {
    lenguajeL1L2 += a;
    lenguajeL1L2 += ' ';
  }
  if (lenguajeL1L2.empty())
    lenguajeL1L2 = "&";
  return lenguajeL1L2;
}

std::string Lenguaje::diferencia(Lenguaje &len) {
  std::string diff;
  bool repeated = false;
  for (const auto &value_L1 : cadenas_del_lenguaje) {
    for (const auto &value_L2 : len.cadenas_del_lenguaje) {
      if (value_L1->get_chain_as_string() == value_L2->get_chain_as_string())
        repeated = true;
    }
    if (!repeated)
      diff += value_L1->get_chain_as_string() + " ";

    repeated = false;
  }
  if (diff.empty())
    diff = "Lenguaje Vacío";

  if (diff == "& ")
    diff = "Lenguaje Vacío";

  return diff;
}

std::string Lenguaje::potencia() {
  int pot;

  std::cout << "Introduce a la potencia que quieres elevar el Lenguaje L1 :" << *this << std::endl;
  std::cout << "> ";
  std::cin >> pot;

  if (pot == 0) {
    return "&";
  }
  Lenguaje len(*this);
  for (int i = 1; i < pot; i++) {
    len.concatenates_with(*this);
    len.op_union(*this);
  }

  std::string pot_chain;
  for (const auto &a : len.cadenas_del_lenguaje) {
    pot_chain += a->get_chain_as_string() + " ";
  }
  if (pot_chain.empty())
    pot_chain = "&";
  return pot_chain;

}

std::string Lenguaje::interseccion(Lenguaje &len) {
  std::string inter;
  for (const auto &value_L1 : cadenas_del_lenguaje)
    for (const auto &value_L2 : len.cadenas_del_lenguaje)
      if (value_L2->get_chain_as_string() == value_L1->get_chain_as_string())
        inter += value_L1->get_chain_as_string() + " ";

  if (inter.empty())
    inter = "Lenguaje Vacío";
  return inter;
}

void Lenguaje::concatenates_with(Lenguaje &len) {
  std::set<Cadena *, compare> copy(cadenas_del_lenguaje);
  for (auto a : copy) {
    for (auto b : len.cadenas_del_lenguaje) {
      if (b->get_real_lenght() == 0) { continue; }
      Cadena aux(*a);
      aux += *b;
      cadenas_del_lenguaje.emplace(new Cadena(aux));
    }
  }
}

std::string Lenguaje::subcadenas() {
  std::string subcadenas;
  std::set<Cadena *, compare> set_subcadenas;
  for (const auto &value_L1 : cadenas_del_lenguaje) {
    for (int i = 0; i < value_L1->get_real_lenght(); i++) {
      for (int j = 1; j <= value_L1->get_real_lenght() - i; j++) {
        if (value_L1->get_chain_as_string().substr(i, j) != "&") {
          auto *aux = new Cadena(value_L1->get_chain_as_string().substr(i, j), alfabeto_);
          set_subcadenas.insert(aux);
        }
      }
    }
  }
  for (const auto &a : set_subcadenas)
    subcadenas += a->get_chain_as_string() + " ";

  return subcadenas;
}

void Lenguaje::opcode_menu(std::ofstream &out, int &opcode, Lenguaje &len) {
  switch (opcode) {
    case 1: out << concatenacion(len) << "\n";
      break;
    case 2: out << op_union(len) << "\n";
      break;
    case 3: out << interseccion(len) << "\n";
      break;
    case 4: out << diferencia(len) << "\n";
      break;
    case 5: out << inversa() << "\n";
      break;
    case 6:out << potencia() << "\n";
      break;
    case 7: out << subcadenas() << "\n";
      break;
    default:throw std::runtime_error("Bad OPCODE");
  }
}
Lenguaje::Lenguaje() {
  alfabeto_ = nullptr;
}
std::set<Cadena *, compare> &Lenguaje::get_cadenas_del_lenguaje() {
  return cadenas_del_lenguaje;
}

Lenguaje &Lenguaje::operator=(const Lenguaje &len) = default;

Alfabeto *Lenguaje::getalfabeto() {
  return alfabeto_;
}
Lenguaje &Lenguaje::operator+(Lenguaje &len) {
  auto *aux = new Lenguaje(*this);
  aux->concatenates_with(len);
  return *aux;
}
Lenguaje &Lenguaje::operator-(Lenguaje &len) {
  auto *aux = new Lenguaje(*this);
  for (auto a : len.cadenas_del_lenguaje)
    aux->cadenas_del_lenguaje.erase(a);

  return *aux;
}
Lenguaje &Lenguaje::operator*(int n) {
  auto *aux = new Lenguaje(*this);
  for (int i = 1; i < n; i++) {
    aux->concatenates_with(*this);
    aux = new Lenguaje(aux->op_union(*this), alfabeto_);
  }
  aux->cadenas_del_lenguaje.insert(new Cadena("&", new Alfabeto("& ")));
  return *aux;
}

Lenguaje &Lenguaje::operator|(Lenguaje &len) {
  auto *alf_aux = new Alfabeto(*alfabeto_ + *len.alfabeto_);
  auto *len_aux = new Lenguaje(this->op_union(len), alf_aux);
  return *len_aux;
}

Lenguaje &Lenguaje::operator^(Lenguaje &len) {
  auto *aux = new Lenguaje(*this);
  aux->interseccion(len);
  return *aux;
}

Lenguaje &Lenguaje::operator!() {
  auto *aux = new Lenguaje(*this);
  aux->inversa();
  return *aux;
}

void Lenguaje::set_tag(const std::string& tag) {
  tag_ = tag;
}


std::string Lenguaje::get_tag() const{
    return tag_;
}
