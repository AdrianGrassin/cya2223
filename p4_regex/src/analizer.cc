#include "../include/analizer.h"


// constructor will analize the file and create the objects
// if it is a comment then it will create a comment object
// comments can be multiline
// if it is a declaration then it will create a declaration object
// if a comment is multiline then it has to read till the end of the comment
// bucles can be for and while

analizer::analizer(std::ifstream &file) {


  // regex

  // comentarios
  std::regex comentario_simple("//.*");
  std::regex comentario_inicio_multilinea("/\\*");
  std::regex comentario_fin_multilinea("\\*/");

  // declaraciones int and double
  std::regex declaracion_simple(R"(int\s+\w+\s*=?.*;|double\s+\w+\s*=?.*;)");
  // no incluir definiciones que en el nombre tengan un parentesis


  // bucles
  std::regex bucle_for(R"(for)");
  std::regex bucle_while(R"(while)");

  // main
  std::regex main(R"(main)");

  //match
  std::smatch match;

  int line_number = 0;
  std::string line;

  while (getline(file, line)) {
    if (std::regex_search(line, match, main)) {
      main_found_ = true;
    }
    line_number++;
    if (std::regex_search(line, match, comentario_simple)) {
      comentarios_.emplace_back(line, line_number);
    } else if (std::regex_search(line, match, comentario_inicio_multilinea)) {
      int line_start = line_number;
      std::string buffer;
      buffer += line + '\n';
      while (getline(file, line)) {
        line_number++;
        buffer += line + '\n';
        if (std::regex_search(line, match, comentario_fin_multilinea)) {
          comentarios_.emplace_back(buffer, line_start, line_number);
          buffer.clear();
          break;
        }
      }
      continue;
    } else if (std::regex_search(line, match, bucle_for)) {
      bucles_.emplace_back(line, line_number);
    } else if (std::regex_search(line, match, bucle_while)) {
      bucles_.emplace_back(line, line_number);
    } else if (std::regex_search(line, match, declaracion_simple)) {
      declaraciones_.emplace_back(line, line_number);
    }
  }

}
std::ostream &operator<<(std::ostream &os, const analizer &analizer) {

  // imprimir descripcion
  if (!analizer.comentarios_.empty()) {
    if (analizer.comentarios_[0].getlinea_p() == 1) {
      os << analizer.comentarios_[0];
    }
  }

  //variables
  os << "VARIABLES: " << std::endl;
  for (const auto &declaracion : analizer.declaraciones_) {
    os << declaracion;
    os << std::endl;
  }
  os << std::endl;

  //statements
  os << "STATEMENTS: " << std::endl;
  for (const auto &bucle : analizer.bucles_) {
    os << bucle;
    os << std::endl;
  }
  os << std::endl;

  //main
  os << "MAIN:" << std::endl;
  if (analizer.main_found_) {
    os << "True" << std::endl;
  } else {
    os << "False" << std::endl;
  }
  os << std::endl;

  // comments
  os << "COMMENTS: " << std::endl;
  for (const auto &comentario : analizer.comentarios_) {
    os << comentario;
  }

  return os;

}
