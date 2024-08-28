#ifndef JUGADOR_CPP
#define JUGADOR_CPP
#include "Jugador.h"

Jugador::Jugador(string nombre) {
  this->nombre = nombre;
  this->dineroActual = 0;
}

// para obtener los atributos
string Jugador::getNombre() { return this->nombre; }

float Jugador::getDineroActual() { return this->dineroActual; }

// para modificar los atributos
void Jugador::setNombre(string nombre) { this->nombre = nombre; }

void Jugador::setDineroActual(float dineroActual) {
  this->dineroActual = dineroActual;
}

// funciones del jugador
void Jugador::agregarDinero(float cantidad) { this->dineroActual += cantidad; }

void Jugador::quitarDinero(float cantidad) { this->dineroActual -= cantidad; }
#endif