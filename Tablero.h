#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
#include <utility>
#include <vector>
using namespace std;

struct Celda {
  bool esMina;
  bool esDescubierta;
  bool exploto;
};

class Tablero {
private:
  int diamantes;
  int minas;

public:
  Tablero();

  bool exploto;
  Celda celdas[5][5];

  void mostrar();
  void descrubrirTodo();
  void generarMinas(int numeroMinas);
  void actualizarEstado();
  bool descrubrirCelda(int i, int j);

  vector<pair<int, int>> getPosicionMinas();

  int getDiamantes();
  int getMinas();
  bool validarCelda(int i, int j);
  bool esDescubierta(int, int);
  bool esMina(int, int);
  bool moverMina(int fromX, int fromY, int toX, int toY);
};
#endif