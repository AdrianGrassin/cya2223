#include "../include/comentarios.h"

static bool already_printed = false;

std::ostream &operator<<(std::ostream &os, const comentarios &comentarios) {
  if (comentarios.lineas_que_abarca_.first == 1 && !already_printed) {
    os << "DESCRIPTION: " << std::endl;
    os << comentarios.comentario_ << std::endl;
    already_printed = true;
  } else if (comentarios.lineas_que_abarca_.first == 1 && already_printed) {
    os << "[Line " << comentarios.lineas_que_abarca_.first << "-" << comentarios.lineas_que_abarca_.second<< "] " << "DESCRIPTION" << std::endl;
  } else if (comentarios.lineas_que_abarca_.first == comentarios.lineas_que_abarca_.second) {
   os << "[Line " << comentarios.lineas_que_abarca_.first << "] " << comentarios.comentario_ << std::endl;
  } else {
    os << "[Line " << comentarios.lineas_que_abarca_.first << " - " << comentarios.lineas_que_abarca_.second << "] ";
    os << comentarios.comentario_ << std::endl;
  }
  return os;
}


