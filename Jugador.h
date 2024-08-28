#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>
using namespace std;

class Jugador {
private:
  string nombre;
  float dineroActual;

public:
  // Constructor
  Jugador(string nombre);

  //para obtener los atributos
  string getNombre();
  float getDineroActual();
  //para modificar los atributos
  void setNombre(string nombre);
  void setDineroActual(float dineroActual);

  
  void agregarDinero(float cantidad);
  void quitarDinero(float cantidad);
};
#endif