#ifndef P3_CALC_H_
#define P3_CALC_H_

#include "include/Alfabeto.h"
#include "include/Lenguaje.h"
#include "include/funciones.h"
#include <stack>

enum tipo_pila {
  Lenguaje_en_pila,
  Numero
};

struct elemento_pila {
  tipo_pila tipo;
  union {
    Lenguaje *lenguaje{};
    int numero;
  } datos;
  elemento_pila(tipo_pila tipo, Lenguaje *lenguaje){
    if(tipo == Lenguaje_en_pila) {
      this->tipo = tipo;
      this->datos.lenguaje = lenguaje;
    } else {
      this->datos.numero = *(int*)&lenguaje;
    }
  }
};

class Calc {
 public:
  explicit Calc(std::ifstream &file);
  ~Calc() = default;

  void operate();

 private:
  void readfile(std::ifstream &file,
                std::vector<std::pair<Alfabeto *, Lenguaje *>> &lista,
                std::vector<std::string> &operaciones);

  static std::string reformatinput(std::string &line);

  Lenguaje concatenar(Lenguaje &l1, Lenguaje &l2);
  Lenguaje diferencia(Lenguaje &l1, Lenguaje &l2);
  Lenguaje potencia(Lenguaje &l1, int &n);
  Lenguaje union_len(Lenguaje &l1, Lenguaje &l2);
  Lenguaje interseccion(Lenguaje &l1, Lenguaje &l2);
  Lenguaje inversa(Lenguaje &l1);
  void perform_operation(char op, std::stack<elemento_pila> &pila);

  std::vector<std::pair<Alfabeto *, Lenguaje *>> definiciones_;
  std::vector<std::string> operaciones_;
  std::vector<std::string> resultados_;

};

#endif //P3_CALC_H_
