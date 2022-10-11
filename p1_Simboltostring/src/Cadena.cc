/**
 * @file Cadena.cc
 *
 * @brief Probablemente sea el fichero que más código tiene ya que la mayoría de operaciones de esta
 * práctica se encuentran a nivel de cadenas.
 */
#include "../include/Cadena.h"

struct compare{
  bool operator()(const Cadena* lhs, const Cadena* rhs) const{
    return lhs->get_chain_as_string() < rhs->get_chain_as_string();
  }
};


Cadena::Cadena(const std::string &linea, Alfabeto *alfabeto_de_la_cadena) {
  alfabeto = alfabeto_de_la_cadena;
  if (linea.empty()) {
    cadena_ = nullptr;
    longitud = 0;
  } else {
    std::string cadenastring = linea.substr(linea.find_last_of(' ') + 1, linea.back());

    set_string(cadenastring);
  }
}

/**
 * @brief Función para imprimir la cadena por pantalla
 */
void Cadena::print_cadena() {
  if (cadena_ != nullptr) {
    for (int i = 0; i < longitud; i++) {
      std::cout << cadena_[i];
    }
    std::cout << std::endl;
  }
}

Cadena::~Cadena() {
  delete cadena_;
}

std::string Cadena::inversa() {
  std::string reversedbuffer;
  for (int i = longitud - 1; i >= 0; i--) {
    reversedbuffer += cadena_[i].getsimbolo();
  }
  return reversedbuffer;
}

std::string Cadena::prefijos() {
  std::string prefixbuffer("& ");
  for (int i = 0; i <= longitud; i++) {
    for (int j = 0; j < i; j++) {
      prefixbuffer += cadena_[j].getsimbolo();
    }
    prefixbuffer += " ";
  }
  return prefixbuffer;
}

std::string Cadena::sufijos() {
  std::string sufixbuffer("& ");
  for (int i = longitud; i > 0; i--) {
    for (int j = i - 1; j < longitud; j++) {
      sufixbuffer += cadena_[j].getsimbolo();
    }
    sufixbuffer += " ";
  }
  return sufixbuffer;
}

std::string Cadena::subcadenas() {
  int maxsized_simbol = 1;
  for (const auto &a : alfabeto->getAlfabeto()) {
    if (maxsized_simbol < a.get_simbolsize()) {
      maxsized_simbol = a.get_simbolsize();
    }
  }

  std::set<std::string> subchains;

  std::string substringbuffer("& ");
  bool checkifinchain = false;
  for (const auto &a : alfabeto->getAlfabeto()) {
    for (int b = 0; b < longitud; b++)
      if (a == cadena_[b]) {
        checkifinchain = true;
        break;
      }
    if (checkifinchain) {
      substringbuffer += a.getsimbolo();
      substringbuffer += " ";
      subchains.insert(a.getsimbolo());
    }
    checkifinchain = false;
  }

  std::string segmentbuff;

  for (int i = 1; i <= longitud; i++) {
    int aux;
    segmentbuff.erase();
    for (int j = 0; j < longitud;) {
      aux = j;
      for (int k = 0; k < i && j < longitud; k++) {
        segmentbuff += cadena_[j++].getsimbolo();
      }
      aux++;
      if (!subchains.count(segmentbuff)) {
        subchains.insert(segmentbuff);
        substringbuffer += segmentbuff;
        substringbuffer += " ";
        segmentbuff.erase();
        j = aux;
      }
    }
  }
  return substringbuffer;
}

void Cadena::opcode_menu(std::ofstream &fileout, int selec) {
  if (cadena_ == nullptr) {
    fileout << "La cadena introducida no pertenece al alfabeto o está vacía" << std::endl;
    return;
  }
  switch (selec) {
    case 1:fileout << std::to_string(longitud) << "\n";
      break;
    case 2:fileout << inversa() << "\n";
      break;
    case 3:fileout << prefijos() << "\n";
      break;
    case 4:fileout << sufijos() << "\n";
      break;
    case 5:fileout << subcadenas() << "\n";
      break;
    default:throw std::runtime_error("Bad OPCODE");
  }
}

void Cadena::set_string(std::string &cadena) {
  int maxsized_simbol = 1;
  for (const auto &a : alfabeto->getAlfabeto()) {
    if (maxsized_simbol < a.get_simbolsize()) {
      maxsized_simbol = a.get_simbolsize();
    }
  }

  std::vector<std::string> solution(0);

  if (!(comprobar_cadena(cadena, maxsized_simbol, 0, 1, solution)) && cadena != CADENA_VACIA) {
    std::cout << "La cadena: " << cadena << " NO pertenece al alfabeto" << std::endl;
    cadena_ = nullptr;
    longitud = 0;
    return;
  }

  if (cadena == CADENA_VACIA)
    solution.emplace_back(CADENA_VACIA);

  longitud = solution.size();
  cadena_ = new Simbolo[longitud];

  for (int rellenar = 0; rellenar < longitud; rellenar++) {
    cadena_[rellenar] = Simbolo(solution[rellenar]);
  }

}

bool Cadena::comprobar_cadena(const std::string &cadena,
                              const int &maxsize,
                              int posicion,
                              int size,
                              std::vector<std::string> &solucion) {
  if (posicion <= -1)
    return false;

  if (posicion + size == cadena.size() + 1 && posicion == cadena.size())
    return true;

  if (posicion + size == cadena.size() + 1)
    return false;

  if (size > maxsize)
    return false;

  std::string cmp(cadena.substr(posicion, size));
  if (alfabeto->getAlfabeto().count(Simbolo(cmp))) {  // si la subcadena está en el alfabeto,
    solucion.push_back(cmp);
    if (comprobar_cadena(cadena, maxsize, posicion + size, 1, solucion)) {
      return true;  // fin
    }
    solucion.pop_back();
    return comprobar_cadena(cadena,
                            maxsize,
                            posicion - size + 1,
                            size + 1,
                            solucion); // se vuelve atras y se incrementa en 1 el tamaño.
  } else {
    return comprobar_cadena(cadena, maxsize, posicion, size + 1, solucion); // se incrementa en 1 el tamaño
  }
}

std::ostream &operator<<(std::ostream &out, Cadena &cad) {
  for (int i = 0; i < cad.longitud; i++) {
    out << cad.cadena_[i];
  }
  return out;
}
bool Cadena::operator<(const Cadena& otracadena) {
  if (longitud < otracadena.longitud)
    return true;
  if (longitud > otracadena.longitud)
    return false;

  for (int i = 0; i < longitud; i++) {
    if (cadena_[i] < otracadena.cadena_[i])
      return true;

    if (otracadena.cadena_[i] < cadena_[i])
      return false;

  }
  return false;
}
int Cadena::get_real_lenght() {
  if (longitud == 1) {
    if (cadena_[0].getsimbolo() == CADENA_VACIA) {
      return 0;
    } else { return 1; }
  }
  else{
    return longitud;
  }
}
std::string Cadena::operator+(Cadena &otracadena) const {
  return get_chain_as_string() + otracadena.get_chain_as_string() ;
}

std::string Cadena::get_chain_as_string() const{
  std::string cadena;
  for(int i = 0; i < longitud; i++){
    cadena += cadena_[i].getsimbolo();
  }
  return cadena;
}


