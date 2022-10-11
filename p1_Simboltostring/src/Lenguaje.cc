//
// Created by grass on 06/10/2022.
//

#include "../include/Lenguaje.h"
#include "../include/funciones.h"

Lenguaje::Lenguaje(const std::string &line, Alfabeto *alfabeto) {
  alfabeto_ = alfabeto;
  std::string string_buffer;
  for (const auto &caracter : line) {
    if (caracter == ' ') {

      cadenas_del_lenguaje.insert(new Cadena(string_buffer, alfabeto));
      string_buffer.clear();
    }
    string_buffer += caracter;
  }
}

std::ostream &operator<<(std::ostream &out, Lenguaje *&len) {
  out << "L = { ";
  for (auto cadena : len->cadenas_del_lenguaje) {
    out << *cadena << " ";
  }
  out << "} ";
  if (len->cadenas_del_lenguaje.empty())
    out << "- Lenguaje Vacío ";

  return out;
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
    default:throw std::runtime_error("Bad OPCODE");
  }
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
      lenguajes_L1L2_concat += *cad_L1 + *cad_L2;
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
    std::cout << value_L2;
  }

  for (const auto &a : lenguajeunion) {
    lenguajeL1L2 += a;
    lenguajeL1L2 += ' ';
  }
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
  return diff;
}

std::string Lenguaje::potencia() {
  int potencia;
  std::cout << "Introduzca cuantas veces quiere aplicar la operación potencia al lenguaje: ";
  std::cin >> potencia;

  std::string len_pot;

  for (auto valueL1 : cadenas_del_lenguaje) {
    if (valueL1->get_real_lenght() == 0)
      continue;
    for (auto value_L1_pasada : cadenas_del_lenguaje) {

    }
  }

  return len_pot;
}
std::string Lenguaje::interseccion(Lenguaje &len) {
  std::string inter;
  for (const auto &value_L1 : cadenas_del_lenguaje)
    for (const auto &value_L2 : len.cadenas_del_lenguaje)
      if (value_L2->get_chain_as_string() == value_L1->get_chain_as_string())
        inter += value_L1->get_chain_as_string() + " ";
  return inter;
}
