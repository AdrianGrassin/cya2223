#include <string>
#include <stdexcept>
#include <algorithm>
#include "../include/BitArray.h"

/***
 * Constructores Básicos de tamaño, copia y movimiento
 ********/

BitArray::BitArray(std::size_t size) {
  bits.resize(size, false);
  RemoveLeadingO(bits);
}

BitArray::BitArray() {
  bits.resize(0, false);
  RemoveLeadingO(bits);
}

BitArray::BitArray(const BitArray &other) {
  bits = other.bits;
  RemoveLeadingO(bits);
}

BitArray::BitArray(BitArray &&other) noexcept {
  bits = other.bits;
  RemoveLeadingO(bits);
}

// takes a number in string format not binary
BitArray::BitArray(const std::string &str) {

  for (const char& c : str) {
    int decimal = c - '0';
    for (int i = 0; i < 4; i++) {
      bits.push_back(decimal % 2);
      decimal /= 2;
    }
  }

 std::reverse(bits.begin(), bits.end());
RemoveLeadingO(bits);

}

/***
 * Operadores de asignación de copia y movimiento
 ********/

BitArray &BitArray::operator=(const BitArray &other) = default;

BitArray &BitArray::operator=(BitArray &&other) noexcept {
  bits = other.bits;
  return *this;
}

/***
 * Métodos de acceso a los bits
 ********/

void BitArray::Set(std::size_t index, const bool &value) {
  if (index >= bits.size()) {
    bits.resize(index + 1, false);
  }
  bits[index] = value;
}

bool BitArray::Get(std::size_t index) const {
  return bits[index];
}

std::size_t BitArray::Size() const {
  return bits.size();
}

void BitArray::Resize(std::size_t size) {
  bits.resize(size);
}

void BitArray::Clear() {
  bits.clear();
}

/***
 * OPERADORES LÓGICOS
 ********//***
 *
 * Operador AND
 * @param lhs
 * @param rhs
 * @return
 */
BitArray operator&(const BitArray &lhs, const BitArray &rhs) {
  BitArray resultado(std::max(lhs.Size(), rhs.Size()));

  for (int i = 0; i < lhs.Size(); ++i) {
    resultado.Set(i, lhs.Get(i) && rhs.Get(i));
  }
  return resultado;
}

/**
 * Operador OR
 * @param lhs (left hand side) primer operando
 * @param rhs (right hand side) segundo operando
 * @return resultado de la operación (BitArray_lhs)(OR)(BitArray_rhs)
 */
BitArray operator|(const BitArray &lhs, const BitArray &rhs) {
  BitArray resultado(std::max(lhs.Size(), rhs.Size()));

  for (int i = 0; i < lhs.Size(); ++i) {
    resultado.Set(i, lhs.Get(i) || rhs.Get(i));
  }

  return resultado;
}

/**
 * Operador XOR
 * @param lhs (left hand side) primer operando
 * @param rhs (right hand side) segundo operando
 * @return resultado de la operación (BitArray_lhs)(XOR)(BitArray_rhs)
 */
BitArray operator^(const BitArray &lhs, const BitArray &rhs) {
  BitArray resultado(std::max(lhs.Size(), rhs.Size()));

  for (int i = 0; i < lhs.Size(); ++i) {
    resultado.Set(i, lhs.Get(i) ^ rhs.Get(i));
  }

  return resultado;
}

/**
 * Operador NOT
 * @param lhs (left hand side) primer operando
 * @return resultado de la operación (NOT)(BitArray_lhs)
 */
BitArray operator~(const BitArray &lhs) {
  BitArray resultado(lhs.Size());

  for (int i = 0; i < lhs.Size(); ++i) {
    resultado.Set(i, !lhs.Get(i));
  }

  return resultado;
}

/**
 * Operador de desplazamiento a la izquierda
 * @param lhs (left hand side) es el operando
 * @param desplazamiento (right hand side) numero de bits a desplazar a la izquierda
 * @return resultado de la operación (BitArray) **
 */
BitArray operator<<(const BitArray &lhs, std::size_t desplazamiento) {
  BitArray resultado(lhs.Size());

  for (int i = 0; i < lhs.Size(); ++i) {
    resultado.Set(i, lhs.Get(i + desplazamiento));
  }

  return resultado;
}

/**
 * Operador de desplazamiento a la derecha
 * @param lhs (left hand side) es el operando
 * @param desplazamiento (right hand side) numero de bits a desplazar a la derecha
 * @return resultado de la operación (BitArray) / (2 ** desplazamiento)
 */
BitArray operator>>(const BitArray &lhs, std::size_t desplazamiento) {
  BitArray resultado(lhs.Size());

  for (int i = 0; i < lhs.Size(); ++i) {
    resultado.Set(i, lhs.Get(i - desplazamiento));
  }

  BitArray::RemoveLeadingO(resultado);
  return resultado;
}

/***
 * Operador de impresión
 * @param os
 * @param bitArray
 * @return
 * */

std::ostream &operator<<(std::ostream &os, const BitArray &bitArray) {
  std::string res;
  for (int i = bitArray.Size(); i > 0; i--) {
    res += ((bitArray.bits[i]) ? '1' : '0');
  }
  os << res;

  return os;
}

int BitArray::GetInt() const {
  int x = 0;
  for (int i = bits.size() - 1; i >= 0; i--) {
    x = x << 1;
    if (bits[i]) {
      x = x | 1;
    }
  }
  return x;
}

/***
 * Operador de inserción
 * */
std::istream &operator>>(std::istream &is, BitArray &bitArray) {
  std::string cadena;
  is >> cadena;
  bitArray.Resize(cadena.size() - 1);
  for (int i = 0; i < cadena.size(); ++i) {
    bitArray.Set(i, cadena[i] == '1');
  }
  return is;
}

BitArray BitArray::operator+(const BitArray &other) const {
  BitArray resultado(std::max(Size() + 1, other.Size() + 1));
  bool acarreo = false;

  for (int i = 0; i < resultado.Size(); ++i) {
    bool suma = Get(i) ^ other.Get(i) ^ acarreo;
    acarreo = (Get(i) && other.Get(i)) || (acarreo && (Get(i) ^ other.Get(i)));
    resultado.Set(i, suma);
  }
  RemoveLeadingO(resultado);
  return resultado;
}

BitArray BitArray::operator-(const BitArray &other) const {
  BitArray resultado(std::max(Size(), other.Size()));
  bool acarreo = false;

  for (int i = 0; i < resultado.Size(); ++i) {
    bool resta = Get(i) ^ other.Get(i) ^ acarreo;
    acarreo = (Get(i) && other.Get(i)) || (acarreo && (Get(i) ^ other.Get(i)));
    resultado.Set(i, resta);
  }
  RemoveLeadingO(resultado);
  return resultado;
}

BitArray BitArray::operator*(const BitArray &other) const {
  BitArray resultado(Size() + other.Size());
  for (int i = 0; i < Size(); ++i) {
    for (int j = 0; j < other.Size(); ++j) {
      resultado.Set(i + j, resultado.Get(i + j) ^ (Get(i) && other.Get(j)));
    }
  }

  RemoveLeadingO(resultado);
  return resultado;
}

BitArray BitArray::operator/(const BitArray &other) const {

}

BitArray BitArray::operator%(const BitArray &other) const {

}

bool BitArray::operator>=(const BitArray &other) const {

}

bool BitArray::operator<=(const BitArray &other) const {

}

bool BitArray::operator>(const BitArray &other) const {

}

bool BitArray::operator<(const BitArray &other) const {

}

bool BitArray::operator==(const BitArray &other) const {
  for (int i = (int) Size() - 1; i >= 0; --i) {
    if (Get(i) != other.Get(i)) {
      return false;
    }
  }
  return true;
}

bool BitArray::operator!=(const BitArray &other) const {
  for (int i = (int) Size() - 1; i < 0; i--) {
    if (Get(i) != other.Get(i)) {
      return true;
    }
  }
  return false;
}

void BitArray::RemoveLeadingO(std::vector<bool> &value) {
  while (value.size() > 1 && !value.back()) {
    value.pop_back();
  }
}

void BitArray::RemoveLeadingO(BitArray &value) {
  while (value.Size() > 1 && !value.Get(value.Size() - 1)) {
    value.bits.pop_back();
  }
}

BitArray::BitArray(const unsigned int &x) {
  for (int i = 0; i < 32; i++) {
    bits.push_back(((x >> i) & 1));
  }
}






