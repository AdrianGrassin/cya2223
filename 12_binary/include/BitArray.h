
#ifndef INC_12_BINARY_INCLUDE_BITARRAY_H_
#define INC_12_BINARY_INCLUDE_BITARRAY_H_

#include <vector>
#include <iosfwd>
#include <bitset>

/***
 * Clase BitArray
 * Representa un vector de bits de tamaño arbitrario y permite realizar operaciones lógicas
 * entre ellos. Los bits se almacenan en un vector de booleanos. El tamaño del vector se puede modificar
 * dinámicamente. Los bits se almacenan en orden inverso para facilitar el eliminado de 0's a la izquierda.
 ******/

class BitArray {
 private:
  std::vector<bool> bits;

 public:
  BitArray();
  explicit BitArray(std::size_t size);

  explicit BitArray(const std::string& str);
  explicit BitArray(const unsigned int& i);
  BitArray(const BitArray &other);
  BitArray(BitArray &&other) noexcept;
  BitArray &operator=(const BitArray &other);
  BitArray &operator=(BitArray &&other) noexcept;

  /***
   * Constructores de enteros de 8, 16, 32 y 64 bits
   ******/

  ~BitArray() = default;

  void Set(std::size_t index, const bool &value);
  static void RemoveLeadingO(std::vector<bool> &value);
  static void RemoveLeadingO(BitArray &value);

  bool Get(std::size_t index) const;
  int GetInt() const;

  std::size_t Size() const;
  void Resize(std::size_t size);

  void Clear();


  /***
   * Operadores de suma, resta, multiplicación y división
   ******/

  BitArray operator+(const BitArray &other) const;
  BitArray operator-(const BitArray &other) const;
  BitArray operator*(const BitArray &other) const;
  BitArray operator/(const BitArray &other) const;
  BitArray operator%(const BitArray &other) const;

  /***
   * Operadores de Comparación
   ******/
  bool operator<=(const BitArray &other) const;
  bool operator>=(const BitArray &other) const;
  bool operator<(const BitArray &other) const;
  bool operator>(const BitArray &other) const;
  bool operator==(const BitArray &other) const;
  bool operator!=(const BitArray &other) const;

  /***
   * Operadores de desplazamiento, AND, OR y XOR
   ******/
  friend BitArray operator&(const BitArray &lhs, const BitArray &rhs);
  friend BitArray operator|(const BitArray &lhs, const BitArray &rhs);
  friend BitArray operator^(const BitArray &lhs, const BitArray &rhs);
  friend BitArray operator~(const BitArray &lhs);
  friend BitArray operator<<(const BitArray &lhs, std::size_t rhs);
  friend BitArray operator>>(const BitArray &lhs, std::size_t rhs);

  /***
   * Operadores de entrada y salida
   ******/
  friend std::ostream &operator<<(std::ostream &os, const BitArray &bitArray);
  friend std::istream &operator>>(std::istream &is, BitArray &bitArray);

};

#endif //INC_12_BINARY_INCLUDE_BITARRAY_H_
