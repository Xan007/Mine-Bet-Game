#ifndef PARTIDA_H
#define PARTIDA_H

#include "Tablero.h"
#include <chrono>
using namespace std;

// Apuestas mayores a esta cifra perderan en el 4to intento
const float CIFRA_PERDER = 30000;

enum EstadoPartida { NoDefinido, Perdido, Ganado };

class Partida {
private:
  Tablero tableroActual;
  float montoApostado;
  float ganancias;
  EstadoPartida estado;
  chrono::steady_clock::time_point ultimoTiempo;

public:
  Partida(float montoApostadoInicial);

  void siguiente();

  EstadoPartida getEstado();
  void setEstado(EstadoPartida nuevoEstado);

  float getMontoApostado();
  float getGanancias();
  float getMontoTotal();

  void guardarTiempo();

  Tablero &getTableroActual();
};
#endif