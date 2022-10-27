#include "../include/bucles.h"
int bucles::contador_buc = 0;

std::ostream &operator<<(std::ostream &os, const bucles &bucles) {
  os << "[Line " << bucles.line_number_ << "] " << "LOOP: " << bucles.tipo_bucle_ << std::endl;
  return os;
}

bucles::bucles(std::string &line, int line_number) {
  line_number_ = line_number;
  contador_buc++;
  if (line.find("for") != std::string::npos) {
    tipo_bucle_ = "FOR";
  } else
    tipo_bucle_ = "WHILE";
}
