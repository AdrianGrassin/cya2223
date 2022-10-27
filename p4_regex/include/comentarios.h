#ifndef UNTITLED_INCLUDE_COMENTARIOS_H_
#define UNTITLED_INCLUDE_COMENTARIOS_H_
#include <iostream>

// clase que crea los objetos comentarios

class comentarios {
  std::string comentario_;
  std::pair<int, int> lineas_que_abarca_;


 public:
    comentarios(std::string &comentario, int line_number) : comentario_(comentario), lineas_que_abarca_(line_number, line_number) {}
    comentarios(std::string &comentario, int line_number, int line_number2) : comentario_(comentario), lineas_que_abarca_(line_number, line_number2) {}

    int getlinea_p() const {return lineas_que_abarca_.first;}


    friend std::ostream &operator<<(std::ostream &os, const comentarios &comentarios);
};

#endif //UNTITLED_INCLUDE_COMENTARIOS_H_
