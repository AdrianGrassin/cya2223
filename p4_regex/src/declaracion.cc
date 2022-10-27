#include "../include/declaracion.h"
int Declaracion::contador_dec = 0;

std::ostream &operator<<(std::ostream &os, const Declaracion &declaracion) {
  os << "[Line " << declaracion.line_number_ << "] ";
  switch (declaracion.variable_.tipo_) {
    case Tipo::tipo_int:os << "INT: ";
      break;
    case Tipo::tipo_double:os << "DOUBLE: ";
      break;
  }
  if (declaracion.variable_.valor_.valor_int_ == 0) {
    os << declaracion.variable_.nombre_;
  } else {
    os << declaracion.variable_.nombre_ << " = " << declaracion.variable_.valor_.valor_int_;
  }
  return os;
}

Variable Declaracion::getVariable(std::string &line) {
  std::regex variable_name(R"(\s[a-z]*)");
  std::regex variable_value(R"(\d+)");
  std::regex variable_type(R"(int|double)");

  std::smatch match;
  std::string nombre;
  std::string tipo;
  std::string valor;
  if (std::regex_search(line, match, variable_name)) {
    nombre = match.str();
    nombre = nombre.substr(1, nombre.size());
  }
  if (std::regex_search(line, match, variable_type)) {
    tipo = match.str();
  }
  if (std::regex_search(line, match, variable_value)) {
    valor = match.str();
  }
  if (tipo == "int") {
    if (valor.empty()) {
      return {nombre, Tipo::tipo_int, 0};
    } else {
      return {nombre, Tipo::tipo_int, std::stoi(valor)};
    }
  }
  if (tipo == "double") {
    if (valor.empty()) {
      return {nombre, Tipo::tipo_double, 0.0};
    } else {
      return {nombre, Tipo::tipo_double, std::stod(valor)};
    }
  }
  return {nombre, Tipo::tipo_int, 0};
}

