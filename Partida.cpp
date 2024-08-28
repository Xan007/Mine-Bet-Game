#ifndef PARTIDA_CPP
#define PARTIDA_CPP

#include "Partida.h"
#include "Tablero.h"
#include "funciones.h"
#include "input_utils.h"

#include <iostream>
using namespace std;

Partida::Partida(float montoApostadoInicial) {
  tableroActual = Tablero();
  tableroActual.generarMinas(5);

  this->ganancias = 0;
  this->montoApostado = montoApostadoInicial;

  this->estado = NoDefinido;
}

void Partida::guardarTiempo() { ultimoTiempo = chrono::steady_clock::now(); }

void Partida::siguiente() {
  if (estado == NoDefinido) {
    int i, j;
    bool descubierta = false;

    do {
      cout << "Introduce la fila (0-4): ";
      i = input_between(0, 4);
      cout << "Introduce la columna (0-4): ";
      j = input_between(0, 4);

      if (!tableroActual.esDescubierta(i, j)) {
        auto ahoraTiempo = chrono::steady_clock::now();

        auto diff = ahoraTiempo - this->ultimoTiempo;

        double elapsedTime = chrono::duration<double>(diff).count();

        bool perderAutomatico = false;

        if (elapsedTime >= 5) {
          perderAutomatico = true;
          cout << "⏳";
        } else if (this->montoApostado >= CIFRA_PERDER &&
                   tableroActual.getDiamantes() >= 3) {
          perderAutomatico = true;
          cout << "✖️";
        }

        if (perderAutomatico) {
          cout << "  ..." << endl;
          cin.ignore();
          vector<pair<int, int>> posiciones = tableroActual.getPosicionMinas();

          pair<int, int> posicionRandom =
              posiciones[rand() % posiciones.size()];

          tableroActual.moverMina(posicionRandom.first, posicionRandom.second,
                                  i, j);
        }
      }

      descubierta = tableroActual.descrubrirCelda(i, j);

      if (!descubierta)
        cout << "[❗] Esta celda ya ha sido descubierta\n\n";

    } while (!descubierta);
  }

  if (tableroActual.exploto == true) {
    estado = Perdido;
    tableroActual.descrubrirTodo();
  } else {
    ganancias =
        montoApostado * (calcularPorcentaje(tableroActual.getDiamantes(), 5));
  }
}

Tablero &Partida::getTableroActual() { return this->tableroActual; }

float Partida::getMontoApostado() { return this->montoApostado; }
float Partida::getGanancias() { return this->ganancias; }
float Partida::getMontoTotal() {
  float montoTotal = this->montoApostado + this->ganancias;
  return montoTotal;
}

EstadoPartida Partida::getEstado() { return estado; }
void Partida::setEstado(EstadoPartida nuevoEstado) { estado = nuevoEstado; }

#endif