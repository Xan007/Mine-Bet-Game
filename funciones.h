#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <cmath>
#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>
using namespace std;

inline string formatoPesosColombianos(float valor) {
  ostringstream out;
  out.imbue(locale(""));
  out << showbase << put_money(static_cast<long long>(valor * 100));
  string str = out.str();

  size_t pos = str.find_first_of("0123456789");
  if (pos != string::npos) {
    str = "$" + str.substr(pos);
  } else {
    str = "$0";
  }

  return str;
}

inline double calcularPorcentaje(int diamantes, int minas) {
  if (diamantes < 1) {
    return 0;
  } else if (diamantes > 20) {
    diamantes = 20;
  }

  double a = 0.13;
  double b = 1.54414;

  double porcentaje = a * pow(b, diamantes - 1);

  porcentaje = min(porcentaje, 5.0);

  return porcentaje;
}

#endif