#ifndef MINAS_H
#define MINAS_H

#include "Jugador.h"
#include "Partida.h"
#include <vector>

class Minas {
private:
  Jugador &jugadorActual;

public:
  vector<Partida*> historialPartidas;
  Partida *partidaActual;
  Partida *mejorPartida;

  Minas(Jugador &jugadorActual);
  bool crearPartidaNueva(float apuesta);
  void retirar();
  void apostar(float monto);
};
#endif