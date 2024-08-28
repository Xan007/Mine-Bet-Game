#include "Jugador.h"
#include "Minas.h"
#include "input_utils.h"

#include "funciones.h"
#include <iostream>
using namespace std;

int main() {
  srand(time(0));

  string nombre;
  float dineroInicial;

  cout << "[💎] Minas [💣]\n\n";
  cout << "Bienvenido por primera vez al juego, por favor registrese:\n\n";

  cout << "Introduce tu nombre:\n>> ";
  getline(cin >> ws, nombre);

  Jugador thisJugador(nombre);

  Minas minasJuego(thisJugador);

  bool mensajeDeposito = false;
  bool mensajeDineroInsuficiente = false;
  bool mensajeGanancias = false;

  do {
    system("clear");
    if (mensajeDeposito) {
      cout << "[💵] Deposito realizado con exito.\n\n";
      mensajeDeposito = false;
    }

    if (mensajeDineroInsuficiente) {
      cout << "[⚠️] No cuentas con el dinero suficiente para realizar esta "
              "apuesta.\n\n";
      mensajeDineroInsuficiente = false;
    }

    if (mensajeGanancias) {
      cout << "[💸] Ganaste "
           << formatoPesosColombianos(minasJuego.partidaActual->getMontoTotal())
           << " [💸]\n\n";
      mensajeGanancias = false;
    }

    cout << "📍 Cuenta:\n* Nombre: " << thisJugador.getNombre() << endl;
    cout << "* Dinero: "
         << formatoPesosColombianos(thisJugador.getDineroActual()) << endl;

    cout << "\n\t\t[💎] Minas [💣]\n";
    cout << "\nBienvenido al juego de las minas, " << thisJugador.getNombre()
         << endl;

    cout << "1. Crear partida nueva\n2. Hacer deposito\n3. Historial de "
            "partidas\n4. Mejor partida\n5. Salir\n";

    int opcion = input_between(1, 5);

    if (opcion == 1) {
      system("clear");
      if (thisJugador.getDineroActual() < 5000) {
        cout
            << "\n[❗] Para poder jugar se necesita un monto minimo de $5,000\n";

        cout << "\nPresione enter para continuar\n";
        cin.ignore();
      } else {
        cout << "Selecciona el monto a apostar:\n";
        cout << "1. $5,000\n";
        cout << "2. $10,000\n";
        cout << "3. $25,000\n";
        cout << "4. $30,000\n";
        cout << "5. $50,000\n";

        int i = 6;

        if (thisJugador.getDineroActual() > 5000) {
          cout << to_string(i++)
               << ". " + formatoPesosColombianos(thisJugador.getDineroActual())
               << "\n";
        }

        cout << to_string(i) << ". Personalizado\n";
        cout << to_string(i + 1) << ". Regresar\n";

        int seleccion;
        seleccion = input_between(1, i + 1);

        float apuesta;
        switch (seleccion) {
        case 1:
          apuesta = 5000;
          break;
        case 2:
          apuesta = 10000;
          break;
        case 3:
          apuesta = 25000;
          break;
        case 4:
          apuesta = 30000;
          break;
        case 5:
          apuesta = 50000;
          break;
        default:
          break;
        }

        if (seleccion == i - 1) {
          apuesta = thisJugador.getDineroActual();
        } else if (seleccion == i) {
          cout << "Introduce el monto personalizado a apostar:";
          do {
            apuesta = input_func<float>();
            if (apuesta < 5000) {
              cout << "El monto minimo es de $5,000\n";
            }
          } while (apuesta < 5000);
        } else if (seleccion == i + 1) {
          continue;
        }

        if (!minasJuego.crearPartidaNueva(apuesta)) {
          mensajeDineroInsuficiente = true;
        }

        if (minasJuego.partidaActual->getEstado() == Ganado) {
          mensajeGanancias = true;
        }
      }
    } else if (opcion == 2) {
      system("clear");
      cout << "Selecciona el monto a depositar:\n1. $10,000\n2. $20,000\n3. "
              "$50,000\n4. $100,000\n5. $200,000\n6. Regresar\n";

      float deposito = 0;

      int opcionDeposito = input_between(1, 6);

      switch (opcionDeposito) {
      case 1:
        deposito = 10000;
        break;

      case 2:
        deposito = 20000;
        break;

      case 3:
        deposito = 50000;
        break;

      case 4:
        deposito = 100000;
        break;

      case 5:
        deposito = 200000;
        break;
      default:
        break;
      }

      if (opcionDeposito == 6)
        continue;

      thisJugador.agregarDinero(deposito);

      mensajeDeposito = true;
    } else if (opcion == 3) {
      system("clear");

      if (minasJuego.historialPartidas.empty()) {
        cout << "[❗] No hay partidas registradas.\n";
      } else {
        cout << "⏰ Historial de partidas:\n\n";
        for (int i = 0; i < minasJuego.historialPartidas.size(); i++) {
          Partida *partida = minasJuego.historialPartidas[i];

          cout << to_string(i + 1) << ".";

          cout << "\n\tEstado: " << setw(25) << left
               << (((partida->getEstado()) == Ganado) ? "Retirado ✅"
                                                      : "Perdido ❌");
          cout << "\n\tApostado:\t" << setw(25) << left
               << formatoPesosColombianos(partida->getMontoApostado())
               << "\n\tGanancias:\t" << setw(25) << left
               << formatoPesosColombianos(partida->getGanancias())
               << "\n\tTotal:\t\t" << setw(25) << left
               << formatoPesosColombianos(partida->getMontoTotal()) << "\n";
        }
      }

      cout << "\nPresione enter para continuar\n";
      cin.ignore();
    } else if (opcion == 4) {
      system("clear");
      if (minasJuego.mejorPartida == nullptr)
        cout << "[❗] Aún no se registra una partida con ganancias.\n";
      else {
        system("clear");
        cout << "[💸] Mejor partida:\n"
        ;
        cout << "Apostado:\t" << setw(25) << left
             << formatoPesosColombianos(
                    minasJuego.mejorPartida->getMontoApostado())
             << "\nGanancias:\t" << setw(25) << left
             << formatoPesosColombianos(minasJuego.mejorPartida->getGanancias())
             << "\nTotal:\t\t" << setw(25) << left
             << formatoPesosColombianos(
                    minasJuego.mejorPartida->getMontoTotal())
             << "\n";
      };

      cout << "\nPresione enter para continuar\n";
      cin.ignore();
    } else if (opcion == 5)
      break;
  } while (true);
}