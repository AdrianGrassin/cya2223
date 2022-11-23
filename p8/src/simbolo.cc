#include "../include/simbolo.h"

/**
 * @brief contador que se utiliza para asignar un id a cada simbolo
 */
static int simbolo_count = 0;


/**
 * @brief Constructor de la clase Simbolo
 * @param simbolo simbolo que se desea crear
 */
Simbolo::Simbolo(const std::string &simbol) {
  simbolo_ = simbol;
}

bool Simbolo::operator==(const Simbolo &otro_simbolo) const {
  return simbolo_ == otro_simbolo.simbolo_;
}

bool Simbolo::operator<(const Simbolo &otro_simbolo) const {
  return simbolo_ < otro_simbolo.simbolo_;
}

bool Simbolo::operator!=(const Simbolo &otro_simbolo) const {
  return simbolo_ != otro_simbolo.simbolo_;
}

std::string Simbolo::ToString() const {
  return simbolo_;
}

/**
 * @brief Metodo que verifica si el simbolo es terminal unitario
 * @return true si el simbolo es terminal unitario, false en caso contrario
 */

bool Simbolo::EsTerminalUnitario() const {
  if (simbolo_.size() > 1) {
    return false;
  }
  if (std::isupper(*simbolo_.c_str())) {
    return false;
  }
  return true;
}

/**
 * @brief Metodo que verifica si el simbolo es no terminal y está en forma normal de chomsky
 * @return true si el simbolo es no terminal, false en caso contrario
 */
bool Simbolo::EsNoTerminalFNC() const {
  if (simbolo_.size() > 2) {
    return false;
  }

  for (auto c : simbolo_) {
    if (!std::islower(c)) {
      return false;
    }
  }
  return true;
}


/**
 * @brief Metodo que devuelve un nuevo simbolo no terminal
 * @return nuevo simbolo no terminal
 */
Simbolo Simbolo::GetNewNonTerminal() {
  return Simbolo( std::string(1, 'F' + simbolo_count++));
}

Simbolo &Simbolo::operator+(const Simbolo &otro_simbolo) {
  simbolo_ += otro_simbolo.simbolo_;
  return *this;
}

std::istream &operator>>(std::istream &is, Simbolo &simbolo) {
  is >> simbolo.simbolo_;
  return is;
}

