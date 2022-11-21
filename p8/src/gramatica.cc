//
// Created by grass on 21/11/2022.
//

#include "../include/gramatica.h"

Gramatica::Gramatica(std::ifstream &archivo) {

  std::string linea;
  std::getline(archivo, linea);

  int n_terminal = std::stoi(linea);
  for (int i = 0; i < n_terminal; i++) {
    std::getline(archivo, linea);
    simbolos_no_terminales_.insert(Simbolo(linea));
  }

  std::getline(archivo, linea);
  int n_nterminales = std::stoi(linea);
  for (int i = 0; i < n_nterminales; i++) {
    std::getline(archivo, linea);
    simbolos_terminales_.insert(Simbolo(linea));
  }

  std::getline(archivo, linea);
  simbolo_inicial_ = Simbolo(linea);

  std::getline(archivo, linea);
  int n_producciones = std::stoi(linea);

  for (int i = 0; i < n_producciones; i++) {
    std::getline(archivo, linea);
    std::stringstream ss(linea);

    Simbolo basura;
    Simbolo no_terminal;
    Simbolo produccion;

    ss >> no_terminal;
    ss >> basura;
    ss >> produccion;

    if (producciones_.find(no_terminal) == producciones_.end()) {
      producciones_[no_terminal] = producciones_.insert({no_terminal, {}}).first->second;
    }
    producciones_[no_terminal].push_back(produccion);
  }

}

std::vector<Simbolo> Gramatica::GetProduccion(const Simbolo &simbolo) const {
  return producciones_.at(simbolo);
}

bool Gramatica::ProduccionUnitaria(const Simbolo &simbolo) const {

}
bool Gramatica::ProduccionVacia(const Simbolo &simbolo) const {
  return producciones_.at(simbolo).size() == 0;
}

/*
1: for all (A → X1X2 . . . Xn (con n ≥ 2, Xi ∈ (Σ ∪ V )) do
2: for all (Xi) do
3: if (Xi = a ∈ Σ) then
4: Add the production Ca → a;
5: Replace Xi with Ca in A → X1X2 . . . Xn;
6: end if
7: end for
8: end for
9: for all (A → B1B2 . . . Bm (con m ≥ 3, Bi ∈ V ) do
10: Add m − 2 non-terminal symbols D1D2 . . . Dm−2;
11: Replace the production A → B1B2 . . . Bm with productions:
12: A → B1D1
13: D1 → B2D2
14: . . .
15: Dm−2 → Bm−1Bm
16: end for
*/

Gramatica Gramatica::ToChomsky() const {
  Gramatica gramatica_chomsky = Gramatica(*this);

  for (auto &produccion : gramatica_chomsky.producciones_) {
    for (auto &simbolo : produccion.second) {
      if (simbolo.ToString().size() > 1) {
        Simbolo nuevo_simbolo = Simbolo(simbolo.ToString().substr(0, 1));
        gramatica_chomsky.simbolos_no_terminales_.insert(nuevo_simbolo);
        gramatica_chomsky.producciones_[nuevo_simbolo] = {simbolo};
        simbolo = nuevo_simbolo;
      }
    }
  }

  for (auto &produccion : gramatica_chomsky.producciones_) {
    if (produccion.second.size() > 2) {
      Simbolo nuevo_simbolo = Simbolo(produccion.second[0].ToString() + produccion.second[1].ToString());
      gramatica_chomsky.simbolos_no_terminales_.insert(nuevo_simbolo);
      gramatica_chomsky.producciones_[nuevo_simbolo] = {produccion.second[1], produccion.second[2]};
      produccion.second = {produccion.second[0], nuevo_simbolo};
    }
  }

  return gramatica_chomsky;

}

void Gramatica::EscribirGramatica(std::ofstream &archivo) const {
  archivo << simbolos_no_terminales_.size() << std::endl;
  for (const auto &simbolo : simbolos_no_terminales_) {
    archivo << simbolo.ToString() << std::endl;
  }
  archivo << simbolos_terminales_.size() << std::endl;
  for (const auto &simbolo : simbolos_terminales_) {
    archivo << simbolo.ToString() << std::endl;
  }
  archivo << simbolo_inicial_.ToString() << std::endl;

  int n_producciones = 0;
  for (const auto &produccion : producciones_) {
    n_producciones += produccion.second.size();
  }
  archivo << n_producciones << std::endl;
  for (const auto &produccion : producciones_) {
    for (const auto &simbolo : produccion.second) {
      archivo << produccion.first.ToString() << " -> " << simbolo.ToString() << std::endl;
    }
  }
}
