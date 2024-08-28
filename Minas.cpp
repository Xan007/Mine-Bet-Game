#ifndef MINAS_CPP
#define MINAS_CPP
#include "Minas.h"
#include "funciones.h"
#include "input_utils.h"
#include <iomanip>
#include <iostream>
using namespace std;

Minas::Minas(Jugador &jugadorActual) : jugadorActual(jugadorActual) {
  mejorPartida = nullptr;
}
bool Minas::crearPartidaNueva(float apuesta) {
  if (jugadorActual.getDineroActual() < apuesta || apuesta < 5000)
    return false;

  historialPartidas.push_back(new Partida(apuesta));

  jugadorActual.quitarDinero(apuesta);

  partidaActual = historialPartidas.back();
  Tablero &tableroActual = partidaActual->getTableroActual();

  do {
    system("clear");
    float porcentajeActual =
        calcularPorcentaje(tableroActual.getDiamantes(), 5);

    cout << "Total: " << formatoPesosColombianos(partidaActual->getMontoTotal())
         << endl;
    cout << "Porcentaje: " << fixed << setprecision(2) << porcentajeActual * 100
         << "%\n";
    cout << "Diamantes: " << tableroActual.getDiamantes() << endl;
    cout << "Minas: " << tableroActual.getMinas() << "\n";

    if (partidaActual->getEstado() == Perdido ||
        partidaActual->getEstado() == Ganado)
      break;

    cout << "\n";

    tableroActual.mostrar();

    partidaActual->guardarTiempo();

    cout << "1. Continuar\n2. Retirar\n";

    int opcion = input_between(1, 2);

    if (opcion == 2) {
      if (porcentajeActual >= 0.30) {
        partidaActual->setEstado(Ganado);
        jugadorActual.agregarDinero(partidaActual->getMontoTotal());
      } else {
        float minimoRetiro = partidaActual->getMontoApostado() +
                             (partidaActual->getMontoApostado() * 0.3);
        cout << "\n[📍] No se puede retirar hasta que se consiga un porcentaje"
                " mayor o igual que 30% ("
             << formatoPesosColombianos(minimoRetiro) << ")\n";

        cout << "\nPresione enter para continuar\n";
        cin.ignore();
      }
    } else
      partidaActual->siguiente();

  } while (true);

  if (partidaActual->getEstado() == Perdido) {
    cout << "\n[❌]     PERDISTE     [❌]\n\n";

    tableroActual.mostrar();
  } else {
    tableroActual.descrubrirTodo();

    cout << "\n[💸]     RETIRO     [💸]\n\n";

    tableroActual.mostrar();

    if (mejorPartida == nullptr) {
      mejorPartida = &(*partidaActual);
    } else {
      if (partidaActual->getGanancias() > mejorPartida->getGanancias()) {
        mejorPartida = partidaActual;
      }
    }
  }

  cout << "\nPresione enter para continuar\n";

  cin.ignore();

  return true;
}
void Minas::retirar() {}
void Minas::apostar(float monto) {}

#endif