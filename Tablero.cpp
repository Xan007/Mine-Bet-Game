#ifndef TABLERO_CPP
#define TABLERO_CPP

#include "Tablero.h"
#include <iostream>
using namespace std;

Tablero::Tablero() {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      Celda c = {};
      c.esMina = false;
      c.esDescubierta = false;
      c.exploto = false;

      this->celdas[i][j] = c;
    }
  }
  this->diamantes = 0;
  this->exploto = false;
}

bool Tablero::esDescubierta(int i, int j) {
  if (!validarCelda(i, j))
    return false;

  return celdas[i][j].esDescubierta;
}

bool Tablero::esMina(int i, int j) {
  if (!validarCelda(i, j))
    return false;

  return celdas[i][j].esMina;
}

void Tablero::generarMinas(int numeroMinas) {
  srand(time(0));
  int minasGeneradas = 0;
  while (minasGeneradas < numeroMinas) {
    int i = rand() % 5;
    int j = rand() % 5;

    if (!this->celdas[i][j].esMina) {
      this->celdas[i][j].esMina = true;
      minasGeneradas++;
    }
  }
  minas = numeroMinas;
}

bool Tablero::descrubrirCelda(int i, int j) {
  if (!validarCelda(i, j))
    return false;

  if (this->celdas[i][j].esDescubierta == true)
    return false;

  this->celdas[i][j].esDescubierta = true;
  this->actualizarEstado();

  if (!this->exploto)
    this->diamantes++;

  return true;
}

bool Tablero::validarCelda(int i, int j) {
  return i >= 0 && i < 5 && j >= 0 && j < 5;
}

bool Tablero::moverMina(int fromX, int fromY, int toX, int toY) {
  if (!validarCelda(fromX, fromY) || !validarCelda(toX, toY))
    return false;

  Celda &fromCelda = this->celdas[fromX][fromY];
  Celda &toCelda = this->celdas[toX][toY];

  if (!fromCelda.esMina)
    return false;

  if (toCelda.esMina)
    return true;

  toCelda.esMina = true;
  fromCelda.esMina = false;

  return true;
}

int Tablero::getDiamantes() { return this->diamantes; }
int Tablero::getMinas() { return this->minas; }

vector<pair<int, int>> Tablero::getPosicionMinas() {
  vector<pair<int, int>> posiciones = {};

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (this->celdas[i][j].esMina)
        posiciones.push_back(make_pair(i, j));
    }
  }

  return posiciones;
}

void Tablero::descrubrirTodo() {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      this->celdas[i][j].esDescubierta = true;
    }
  }
}

void Tablero::actualizarEstado() {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      Celda &estaCelda = this->celdas[i][j];
      if (estaCelda.esDescubierta == true && estaCelda.esMina == true) {
        this->exploto = true;
        estaCelda.exploto = true;
        break;
      }
    }
  }
}

void Tablero::mostrar() {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      Celda &c = this->celdas[i][j];

      cout << "|";
      if (c.esDescubierta) {
        if (c.esMina) {
          if (c.exploto)
            cout << "💥";
          else
            cout << "💣";
        } else {
          cout << "💎";
        }
      } else {
        cout << "❓";
      }
      cout << "| ";
    }
    cout << "\n";
  }
}

#endif