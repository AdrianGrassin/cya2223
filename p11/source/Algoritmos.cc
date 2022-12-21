#include "../include/Algoritmos.h"

std::vector<int> calcular_monedas(double total, std::vector<int> &monedas) {
  std::vector<int> resultado;
  int total_int = total * 100;

  // algoritmo de cambio de monedas voraz
  int i = monedas.size() - 1;
  while (total_int > 0) {
    if (total_int >= monedas[i]) {
      total_int -= monedas[i];
      resultado.push_back(monedas[i]);
    } else {
      i--;
    }
  }
  return resultado;
}

std::string sol_str_basic(std::vector<int> &resultado) {
  std::string solucion = "Solucion:";
  for (int i : resultado) {
    if (i < 100) {
      solucion += " " + std::to_string(i) + "c";
    } else {
      solucion += " " + std::to_string(i / 100) + "e";
    }
  }
  return solucion;
}

std::string sol_str_tipo(std::vector<int> &resultado) {
  std::string solucion = "Solucion: ";
  int count = 1;
  for (int i = 0; i < resultado.size(); i++) {
    if ((i + 1) < resultado.size()) {
      if (resultado[i] == resultado[i + 1]) {
        count++;
      } else {
        if (resultado[i] < 100) {
          if (count == 1)
            solucion += std::to_string(resultado[i]) + "c ";
          else
            solucion += std::to_string(count) + "x" + std::to_string(resultado[i]) + "c ";
        } else {
          if (count == 1)
            solucion += std::to_string(resultado[i] / 100) + "e ";
          else
            solucion += std::to_string(count) + "x" + std::to_string(resultado[i] / 100) + "e ";
        }

        count = 1;
      }
    } else {
      if (resultado[i] < 100) {
        if (count == 1)
          solucion += std::to_string(resultado[i]) + "c ";
        else
          solucion += std::to_string(count) + "x" + std::to_string(resultado[i]) + "c ";
      } else {
        if (count == 1)
          solucion += std::to_string(resultado[i] / 100) + "e ";
        else
          solucion += std::to_string(count) + "x" + std::to_string(resultado[i]) + "e ";
      }
    }
  }

  return solucion;
}


std::vector<int> calcular_monedas_eficiente(double total, std::vector<int>& monedas) {
  std::vector<int> solucion;
  int total_int = total * 100;
  int suma = 0;
  for (int i = monedas.size() - 1; i >= 0; i--) {
    int cantidad = (total_int - suma) / monedas[i];
    if (cantidad > 0) {
      for (int j = 0; j < cantidad; j++) {
        solucion.push_back(monedas[i]);
      }
      suma += cantidad * monedas[i];
    }
  }
  return solucion;
}